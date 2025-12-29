#include "threshold_on_bandpower/thresholding.h"

ThresholdingNode::ThresholdingNode() {
	if(!setParams()) {
		ROS_ERROR("Invalid node configuration, quitting...");
		ros::shutdown();
	}
	else {
		// Initialize ros components
		this->thresholding_pub_ = nh_.advertise<rosneuro_msgs::NeuroEvent>("/events/bus", 1);
		this->bandpower_sub_ = nh_.subscribe("/eeg/bandpower", 1, &ThresholdingNode::thresholdingCallback, this);
	}
}

// Set custom input params
bool ThresholdingNode::setParams() {
    if(!ros::param::get("~channel", this->channel)) {
        ROS_ERROR("Missing 'channel' in the server. 'channel' is a mandatory parameter");
        return false;
    }

    if(!ros::param::get("~threshold", this->threshold)) {
        ROS_ERROR("Missing 'threshold' in the server. 'threshold' is a mandatory parameter");
        return false;
    }

    return true;
}

// Callback
void ThresholdingNode::thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	if(this->channel > msg->eeg.info.nchannels) {
		ROS_ERROR("Input channel number is not valid");
		return;
	}

	if(msg->eeg.data[this->channel-1] > this->threshold) {
		rosneuro_msgs::NeuroEvent out_msg;
		out_msg.event = 10;
		this->thresholding_pub_.publish(out_msg);
		ROS_INFO("A new NeuroEvent have been published");
	}

	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "thresholding_node");
	
	ThresholdingNode thresholding_node;
	
	ros::spin();	
	
	return 0;
}

