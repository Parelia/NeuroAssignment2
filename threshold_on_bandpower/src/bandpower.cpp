/*
	@file	bandpower.cpp
	@brief	Computes the power band of filtered EEG signals and publishes the results
	@author	404 Brain Not Found
*/

#include "threshold_on_bandpower/bandpower.h"

// Constructor for the BandPowerNode class
BandPowerNode::BandPowerNode() : ex_n(0) {
	// Initialize ROS components: Publisher and Subscriber
	this->filtered_sub_ = nh_.subscribe("/neurodata", 1, &BandPowerNode::bandpowerCallback, this);
	this->bandpower_pub_ = nh_.advertise<rosneuro_msgs::NeuroFrame>("/neurodata_bandpower", 1);
}

// Function to generate a new EEG frame with updated data
rosneuro_msgs::NeuroFrame BandPowerNode::newEEGFrameFromOld(const rosneuro_msgs::NeuroFrame& old_msg, const std::vector<float>& new_data) {
	// Create a copy of the old message to retain existing structure
	rosneuro_msgs::NeuroFrame new_msg = old_msg;
	
	// Update the components of the new message
	new_msg.eeg.info.nchannels = new_data.size();
	new_msg.eeg.info.nsamples = 1; // Averages output
	new_msg.eeg.data = new_data;
	
	return new_msg;
}

// Callback function that processes incoming EEG data and performs thresholding
void BandPowerNode::bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	// Extract the number of channels and samples from the incoming message
	int nchannels = msg->eeg.info.nchannels;
	int nsamples = msg->eeg.info.nsamples;

	// Initialize buffer on the first callback (for the first batch of data)
	if(this->ex_n == 0) {
		this->buffer.resize(nchannels, std::vector<float>(msg->sr, 0.0f));
		this->averages.resize(nchannels, 0.0f);
	}
	// Increment the counter to track the number of processed frames
	this->ex_n++;
		
	// Buffer operations: discard old data and store the new one
	for(int i=0; i < nchannels; i++) {
		// Remove the oldest data
		this->buffer[i].erase(this->buffer[i].begin(), this->buffer[i].begin() + nsamples);

		// Add the new data to the end of the buffer
		this->buffer[i].insert(this->buffer[i].end(), msg->eeg.data.begin() + i * nsamples, msg->eeg.data.begin() + (i + 1) * nsamples);
	}

	// Compute the bandpower only if the buffer is filled with enough data
	if(this->ex_n * nsamples >= msg->sr) {
		for(int i=0; i < nchannels; i++) {
			float current_bandpower = 0.0;
			// Compute the bandpower for each channel (square -> log -> mean)
			for(int j=0; j < buffer[i].size(); j++) {
				current_bandpower += std::log(this->buffer[i][j] * this->buffer[i][j] + 1e-12);
				ROS_INFO("Buffer on %i, %i: %f", i+1 ,j,this->buffer[i][j]);
			}
			this->averages[i] = current_bandpower / this->buffer[i].size();
			ROS_INFO("Average channel %i: %f", i+1,this->averages[i]);
		}
	}

	// Publish the computed result
	this->bandpower_pub_.publish(newEEGFrameFromOld(*msg, this->averages));
	
	return;
}


// Main function to initialize the ROS node and start the event loop
int main(int argc, char** argv) {

	ros::init(argc, argv, "bandpower_node");
	
	BandPowerNode bandpower_node;
	
	ros::spin();			
	
	return 0;
}

