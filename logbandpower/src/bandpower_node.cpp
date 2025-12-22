#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>


ros::Publisher bandpower_pub;
ros::Subscriber filtered_sub;


void bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
/*
	signal = signal * signal;
	std::log(signal + + 1e-12);
	
	rosneuro_msgs::NeuroFrame new_msg;
	bandpower_pub..publish(new_msg);
	*/
}

rosneuro_msgs::NeuroFrame newFrameFromOld(const rosneuro_msgs::NeuroFrame::ConstPtr& old_msg, const rosneuro_msgs::NeuroDataFloat& new_eeg) {
	rosneuro_msgs::NeuroFrame new_msg(old_msg);
	new_eeg.info = old_msg->info;
	new_msg.eeg = new_eeg;
	return new_msg;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "bandpower_node");
	
	ros::NodeHandle n;
	
	bandpower_pub = n.advertise<rosneuro_msgs::NeuroFrame>("/eeg/bandpower", 1);
	
	filtered_sub = n.subscribe("/eeg/filtered", 1, bandpowerCallback);
	
	ros::spin();			
	
	return 0;
}

