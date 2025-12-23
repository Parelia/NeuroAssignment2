#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <rosneuro_msgs/NeuroEvent.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>


ros::Publisher thresholding_pub;
ros::Subscriber bandpower_sub;

int channel;
float threshold;


void thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	ROS_INFO("Channel: %d", msg->eeg.info.nchannels);
	if(msg->eeg.info.nchannels > channel) {
		ROS_INFO("Channel number error");
		return;
	}

	std::vector<float>::const_iterator first = msg->eeg.data.begin();
	std::vector<float>::const_iterator last = msg->eeg.data.begin() + 32;
	std::vector<float> data(first, last);
	

	for(int i=0; i < data.size(); i++){
		//ROS_INFO("out");
		if(data[i] > threshold) {
			rosneuro_msgs::NeuroEvent out_msg;
			out_msg.event = 10;
			thresholding_pub.publish(out_msg);
		}
	}


	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "thresholding_node");
	
	ros::NodeHandle n;
	
    	n.param("channel", channel, 1);
    	n.param("threshold", threshold, float(10));
	
	thresholding_pub = n.advertise<rosneuro_msgs::NeuroEvent>("/events/bus", 1);
	
	bandpower_sub = n.subscribe("/eeg/bandpower", 1, thresholdingCallback);
	
	ros::spin();			
	
	return 0;
}

