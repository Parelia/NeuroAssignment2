#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <rosneuro_msgs/NeuroEvent.h>

class ThresholdingNode {
	private:
		ros::NodeHandle nh_;
		ros::Publisher thresholding_pub_;
		ros::Subscriber bandpower_sub_;
		
		int channel;
		float threshold;

	public:
		ThresholdingNode();
		bool setParams();
		void thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr&);
};

#endif
