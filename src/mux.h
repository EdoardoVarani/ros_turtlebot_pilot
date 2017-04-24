#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ros_turtlebot_pilot/SetMode.h"

class Mux {
private: 
    ros::NodeHandle Handle;
    ros::Subscriber joySub;
    ros::Subscriber autoSub;
    ros::Publisher cmdPub;
    ros::ServiceServer modeSr;
    geometry_msgs::Twist command;
    int mode;
        
    void joyCallback(const geometry_msgs::Twist::ConstPtr& msg);
    void autoCallback(const geometry_msgs::Twist::ConstPtr& msg);
    bool modeService(ros_turtlebot_pilot::SetMode::Request &req, ros_turtlebot_pilot::SetMode::Response &res);
public:    
    void Prepare();
    void RunContinuously();
    void RunPeriodically();
};