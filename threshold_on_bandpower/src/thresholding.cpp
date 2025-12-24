#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <rosneuro_msgs/NeuroEvent.h>

// Global variables
int channel;
float threshold;
ros::Publisher thresholding_pub;

// Callback
void thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	ROS_INFO("Channel: %d", msg->eeg.info.nchannels);
	if(channel > msg->eeg.info.nchannels) {
		ROS_ERROR("Input channel number is not valid");
		return;
	}

	if(msg->eeg.data[channel-1] > threshold) {
		rosneuro_msgs::NeuroEvent out_msg;
		out_msg.event = 10;
		thresholding_pub.publish(out_msg);
	}

	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "thresholding_node");
	
	ros::NodeHandle nh;
	nh.param("channel", channel, 1);
	nh.param("threshold", threshold, 10.0f);
	
	thresholding_pub = nh.advertise<rosneuro_msgs::NeuroEvent>("/events/bus", 1);
	
	ros::Subscriber bandpower_sub = nh.subscribe("/eeg/bandpower", 1, thresholdingCallback);
	
	ros::spin();			
	
	return 0;
}

