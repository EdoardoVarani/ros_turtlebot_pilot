#include "joy_cmd.h"


#define RUN_PERIOD_DEFAULT 0.1
#define NAME_OF_THIS_NODE "joy_cmd"


void JoyCmd::Prepare() {
    // obtain a subscriber to the topic joy, where the input are read
    joySub = handle.subscribe("joy", 10, &JoyCmd::joyCallback, this);

    // obtain a publisher to the cmd_joy topic where turtlebot read the command
    cmdPub = handle.advertise<geometry_msgs::Twist>("cmd_joy", 10);
    
    // obtain the service client
    if (ros::service::exists("mode", true)) { //true for print possible error reason
	client = handle.serviceClient<ros_turtlebot_pilot::SetMode>("mode");
	ros_turtlebot_pilot::SetMode msg;
	msg.request.mode = 0;
	client.call(msg);
    }
    
    // obtain the values max_linear and max_angular from the parameter server and 
    // store them in the maxLinear and maxAngular variable
    handle.param("/max_linear", maxLinear, 1.0);
    handle.param("/max_angular", maxAngular, 1.0);    
    
    
    ROS_INFO("Node %s ready to run.", ros::this_node::getName().c_str());
}

void JoyCmd::joyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
    //set the mode through the service offered by mux
    if(msg->buttons[0]){
	
    }
    
    // geometry_msgs::Twist out;
    //left analog up/down
    out.linear.x = maxLinear * msg->axes[1];
    
    //right analog left/right
    out.angular.z = maxAngular * msg->axes[3];
    
    //cmdPub.publish(out);
}

void JoyCmd::RunContinuously() {
    ros::spin();
}

void JoyCmd::RunPeriodically () {
    ros::Rate r(10);
    ros::Rate r1(1/RUN_PERIOD_DEFAULT);
    
    while(ros::ok()) {
        ros::spinOnce();
        cmdPub.publish(out);
        r.sleep();
    }
}

int main(int argc, char **argv) {
  ros::init(argc, argv, NAME_OF_THIS_NODE);
  JoyCmd mNode;
   
  mNode.Prepare();
  //mNode.RunContinuously();
  mNode.RunPeriodically();
  
  return (0);
}










