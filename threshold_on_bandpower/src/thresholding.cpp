#include "threshold_on_bandpower/thresholding.h"

ThresholdingNode::ThresholdingNode() {
	// Initialize ros components
	this->thresholding_pub_ = nh_.advertise<rosneuro_msgs::NeuroEvent>("/events/bus", 1);
	this->bandpower_sub_ = nh_.subscribe("/eeg/bandpower", 1, &ThresholdingNode::thresholdingCallback, this);
	
	// Get input params
	this->nh_.param("channel", this->channel, 1);
	this->nh_.param("threshold", this->threshold, 1.0f);
}

// Callback
void ThresholdingNode::thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	ROS_INFO("Channel: %d", msg->eeg.info.nchannels);
	if(this->channel > msg->eeg.info.nchannels) {
		ROS_ERROR("Input channel number is not valid");
		return;
	}

	if(msg->eeg.data[this->channel-1] > this->threshold) {
		rosneuro_msgs::NeuroEvent out_msg;
		out_msg.event = 10;
		this->thresholding_pub_.publish(out_msg);
	}

	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "thresholding_node");
	
	ThresholdingNode thresholding_node;
	
	ros::spin();	
	
	return 0;
}

