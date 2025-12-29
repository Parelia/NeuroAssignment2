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
		
		int ex_n;									// Execution number to wait until buffer is filled
		std::vector<std::vector<float>> buffer_;	// [channel x samples]
		std::vector<float> averages_;				// [channel x 1]

	public:
		BandPowerNode();
		rosneuro_msgs::NeuroFrame newEEGFrameFromOld(const rosneuro_msgs::NeuroFrame&, const std::vector<float>&);
		void bandpowerCallback(const rosneuro_msgs::NeuroFrame::ConstPtr&);
};

#endif
