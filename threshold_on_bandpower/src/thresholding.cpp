/*
	@file	thresholding.cpp
	@brief	Implements a thresholding operation to detect relevant EEG values
	@author	404 Brain Not Found
*/

#include "threshold_on_bandpower/thresholding.h"

// Constructor for the ThresholdingNode class
ThresholdingNode::ThresholdingNode() {
	// Attempt to set parameters for the node, if it fails, shutdown the node
	if(!setParams()) {
		ROS_ERROR("Invalid node configuration, quitting...");
		ros::shutdown();
	} else {
		// Initialize ROS components: Publisher and Subscriber
		this->bandpower_sub_ = nh_.subscribe("/neurodata", 1, &ThresholdingNode::thresholdingCallback, this);
		this->thresholding_pub_ = nh_.advertise<rosneuro_msgs::NeuroEvent>("/neurodata_event", 1);
	}
}

// Function to set parameters for the node (channel and threshold values)
bool ThresholdingNode::setParams() {
	// Get the channel parameter from the ROS server
    if(!ros::param::get("~channel", this->channel)) {
        ROS_ERROR("Missing 'channel' in the server. 'channel' is a mandatory parameter");
        return false;
    }

	// Get the threshold value from the ROS server
    if(!ros::param::get("~threshold", this->threshold)) {
        ROS_ERROR("Missing 'threshold' in the server. 'threshold' is a mandatory parameter");
        return false;
    }
	
    return true;
}

// Callback function that processes incoming EEG data and performs thresholding
void ThresholdingNode::thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	// Ensure the channel number is valid before accessing data
	if(this->channel > msg->eeg.info.nchannels) {
		ROS_ERROR("Input channel number is not valid for incoming EEG");
		return;
	}
	
	// Check if the EEG value from the specified channel exceeds the threshold
	if(msg->eeg.data[this->channel-1] > this->threshold) {
		// Create a new NeuroEvent message and publish it
		rosneuro_msgs::NeuroEvent out_msg;
		out_msg.event = 10;
		
		this->thresholding_pub_.publish(out_msg);
		ROS_INFO("A new NeuroEvent have been published");
	}

	return;
}


// Main function to initialize the ROS node and start the event loop
int main(int argc, char** argv) {

	ros::init(argc, argv, "thresholding_node");
	
	ThresholdingNode thresholding_node;
	
	ros::spin();	
	
	return 0;
}

