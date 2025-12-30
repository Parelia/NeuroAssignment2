/*
	@file	thresholding.h
	@brief	Header file for the ThresholdingNode class that performs a thresholding operation to detect relevant EEG values
	@author	404 Brain Not Found
*/

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
		// Constructor for the ThresholdingNode class
		ThresholdingNode();
		
		// Function to set parameters for the node (channel and threshold values)
		bool setParams();
		
		// Callback function that processes incoming EEG data and performs thresholding
		void thresholdingCallback(const rosneuro_msgs::NeuroFrame::ConstPtr&);
};

#endif
