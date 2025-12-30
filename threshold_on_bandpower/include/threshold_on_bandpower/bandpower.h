/*
	@file	bandpower.h
	@brief	Header file for the BandPowerNode class that performs the computation of the power band of filtered EEG signals and publishes the results
	@author	404 Brain Not Found
*/

#ifndef BANDPOWER_H
#define BANDPOWER_H

#include <ros/ros.h>
#include <rosneuro_msgs/NeuroFrame.h>
#include <vector>

class BandPowerNode {
	private:
		ros::NodeHandle nh_;
		ros::Publisher bandpower_pub_;
		ros::Subscriber filtered_sub_;
		
		int ex_n;								// Execution number to wait until buffer is filled
		std::vector<std::vector<float>> buffer;	// [channel x samples]
		std::vector<float> averages;			// [channel x 1]

	public:
		// Constructor for the BandPowerNode class
		BandPowerNode();
		
		// Function to generate a new EEG frame with updated data
		rosneuro_msgs::NeuroFrame newEEGFrameFromOld(const rosneuro_msgs::NeuroFrame&, const std::vector<float>&);
		
		// Callback function that processes incoming filtered EEG data
		void bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr&);
};

#endif
