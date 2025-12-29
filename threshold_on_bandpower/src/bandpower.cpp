#include "threshold_on_bandpower/bandpower.h"

BandPowerNode::BandPowerNode() : ex_n(0) {
	// Initialize ros components
	this->bandpower_pub_ = nh_.advertise<rosneuro_msgs::NeuroFrame>("/eeg/bandpower", 1);
	this->filtered_sub_ = nh_.subscribe("/eeg/filtered", 1, &BandPowerNode::bandpowerCallback, this);
}

// Compute out data
rosneuro_msgs::NeuroFrame BandPowerNode::newEEGFrameFromOld(const rosneuro_msgs::NeuroFrame& old_msg, const std::vector<float>& new_data) {
	rosneuro_msgs::NeuroFrame new_msg = old_msg;
	
	new_msg.eeg.info.nchannels = new_data.size();
	new_msg.eeg.info.nsamples = 1;
	new_msg.eeg.data = new_data;
	
	return new_msg;
}

// Sub callback: extract, store and compute data, then publish
void BandPowerNode::bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	// New data info
	int nchannels = msg->eeg.info.nchannels;
	int nsamples = msg->eeg.info.nsamples;

	// Only on first call, initialize buffers
	if(this->ex_n == 0) {
		this->buffer_.resize(nchannels, std::vector<float>(msg->sr, 0.0f));
		this->averages_.resize(nchannels, 0.0f);
	}
	this->ex_n++;
		
	// Buffer operations wrapped in one cycle
	for(int i=0; i < nchannels; i++) {
		// Remove the old data
		this->buffer_[i].erase(this->buffer_[i].begin(), this->buffer_[i].begin() + nsamples);

		// Dynamically add new data
		this->buffer_[i].insert(this->buffer_[i].end(), msg->eeg.data.begin() + i * nsamples, msg->eeg.data.begin() + (i + 1) * nsamples);
	}

	// Compute the bandpower [square - log - mean]
	if(this->ex_n * nsamples >= msg->sr) { // wait until buffer is filled
		for(int i=0; i < nchannels; i++) {
			float current_bandpower = 0.0;
			for(int j=0; j < buffer_[i].size(); j++)
				current_bandpower += std::log(this->buffer_[i][j] * this->buffer_[i][j] + 1e-12);
			this->averages_[i] = current_bandpower / this->buffer_[i].size();
		}
	}

	// Publish result 
	this->bandpower_pub_.publish(newEEGFrameFromOld(*msg, this->averages_));

	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "bandpower_node");
	
	BandPowerNode bandpower_node;
	
	ros::spin();			
	
	return 0;
}

