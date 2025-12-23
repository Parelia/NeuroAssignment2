#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>


class BandPowerNode {
	private:
		ros::NodeHandle nh_;
		ros::Publisher bandpower_pub_;
		ros::Subscriber filtered_sub_;
		
		int ex_n;									// Exectution number to wait until buffer is filled
		std::vector<std::vector<float>> buffer_;	// [channel x samples]
		std::vector<float> averages_;				// [channel x 1]

	public:
		BandPowerNode() : ex_n(0) {
			// Initialize ros components
			bandpower_pub_ = nh_.advertise<rosneuro_msgs::NeuroFrame>("/eeg/bandpower", 1);
			filtered_sub_ = nh_.subscribe("/eeg/filtered", 1, &BandPowerNode::bandpowerCallback, this);
		}
		
		// Compute out data
		rosneuro_msgs::NeuroFrame newEEGFrameFromOld(const rosneuro_msgs::NeuroFrame& old_msg, const std::vector<float>& new_data) {
			rosneuro_msgs::NeuroFrame new_msg = old_msg;
			
			new_msg.eeg.info.nchannels = new_data.size();
			new_msg.eeg.info.nsamples = 1;
			new_msg.eeg.data = new_data;
			
			return new_msg;
		}
	
		// Sub callback: extract, store and compute data, then publish
		void bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
			// New data info
			int nchannels = msg->eeg.info.nchannels;
			int nsamples = msg->eeg.info.nsamples;
		 	
		 	// Only on first call, initialize buffers
			if(ex_n == 0) {
				buffer_.resize(nchannels, std::vector<float>(msg->sr, 0.0f));
				averages_.resize(nchannels, 0.0f);
			}
			ex_n++;
		    
		    // Buffer operations wrapped in one cycle
		    for(int i=0; i < nchannels; i++) {
		   		// Remove the old data
		        buffer_[i].erase(buffer_[i].begin(), buffer_[i].begin() + nsamples);

		    	// Dynamically add new data
		        buffer_[i].insert(buffer_[i].end(), msg->eeg.data.begin() + i * nsamples, msg->eeg.data.begin() + (i + 1) * nsamples);
		    }

		    // Compute the bandpower [square - log - mean]
		    if(ex_n * nsamples >= msg->sr) { // wait until buffer is filled
		        for(int i=0; i < nchannels; i++) {
		            float current_bandpower = 0.0;
		            for(int j=0; j < buffer_[i].size(); j++)
		                current_bandpower += std::log(buffer_[i][j] * buffer_[i][j] + 1e-12);
		            averages_[i] = current_bandpower / buffer_[i].size();
		        }
		    }
		    
		    // Publish result 
		    bandpower_pub_.publish(newEEGFrameFromOld(*msg, averages_));
			
			return;
		}
};


int main(int argc, char** argv) {

	ros::init(argc, argv, "bandpower_node");
	
	BandPowerNode bandpower_node;
	
	ros::spin();			
	
	return 0;
}

