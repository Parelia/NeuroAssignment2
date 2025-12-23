#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>


ros::Publisher bandpower_pub;
ros::Subscriber filtered_sub;


rosneuro_msgs::NeuroFrame newEegFrameFromOld(const rosneuro_msgs::NeuroFrame& old_msg, const rosneuro_msgs::NeuroDataFloat& new_eeg) {
	rosneuro_msgs::NeuroFrame new_msg = old_msg;
	new_msg.eeg = new_eeg;
	new_msg.eeg.info = old_msg.eeg.info;
	return new_msg;
}

void bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr& msg) {
	rosneuro_msgs::NeuroDataFloat new_eeg = msg->eeg;
	for(int i=0; i < new_eeg.data.size(); i++) {
		new_eeg.data[i] = msg->eeg.data[i] * msg->eeg.data[i];
		new_eeg.data[i] = std::log(new_eeg.data[i] + 1e-12);
	}
	
	bandpower_pub.publish(newEegFrameFromOld(*msg, new_eeg));
	
	return;
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "bandpower_node");
	
	ros::NodeHandle n;
	
	bandpower_pub = n.advertise<rosneuro_msgs::NeuroFrame>("/eeg/bandpower", 1);
	
	filtered_sub = n.subscribe("/eeg/filtered", 1, bandpowerCallback);
	
	ros::spin();			
	
	return 0;
}

