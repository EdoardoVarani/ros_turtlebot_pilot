#ifndef _JOYPAD_SIMULATOR
#define _JOYPAD_SIMULATOR

#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#include <cstdlib>
#include <map>

class JoyPadSimulator{
private: ros::NodeHandle nodeHandle;
	ros::Publisher pub;
	sensor_msgs::Joy msg_out;
	struct termios oldt,newt;
	std::map<int,int> buttonMap;
	void printMenu();
	///\brief setup terminal in raw mode disabling echo
	void setupTerminal();
	///\brief restore old settings
	void restoreTerminal();

	
public: 
  void Prepare();
  void RunPeriodically();
  
};

#endif