#include "joypad_simulator.hh"
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define ARROW1 27
#define ARROW2 91

void JoyPadSimulator::Prepare()
{
   // publish on the topic joy
    pub = nodeHandle.advertise<sensor_msgs::Joy>("joy", 10);
}

void JoyPadSimulator::RunPeriodically()
{
    setupTerminal();
    while(ros::ok()){
      sensor_msgs::Joy msg;
      cout << "" << msg.axis.le;
      int c = getchar();
      msg.header.stamp = ros::Time().now();
      switch (c){
	case KEY_LEFT:
	  msg.axes[3] = -1;
	  break;
	case KEY_RIGHT:
	   msg.axes[3] = -1;
	   break;
	case KEY_UP:
	   msg.axes[1] = 1;
	   break;
	case KEY_DOWN:
	   msg.axes[1] = -1;
	   break;
      };
      pub.publish(msg);
      
    }
    
    restoreTerminal();
}

void JoyPadSimulator::setupTerminal(){
  // tcgetattr gets parameters of the current terminal
  // STDIN_FILENO will tell tcgetattr that it should write the setting of stdin to oldt
  tcgetattr(STDIN_FILENO, &this->oldt);
  
  // copy settings
  this->newt = this->oldt;
  
  // disable echo and end set raw mode
  this->newt.c_lflag &= ~(ICANON | ECHO);
  
  // set new settings to STDIN TCSANOW tells tcsetattr to change attributes now
  tcsetattr(STDIN_FILENO,TCSANOW, &this->newt);
}

void JoyPadSimulator::restoreTerminal(){
    tcsetattr(STDIN_FILENO,TCSANOW,&this->oldt);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "joypad_simulator");
  JoyPadSimulator mNode;
   
  mNode.Prepare();
  //mNode.RunContinuously();
  mNode.RunPeriodically();
  
  return (0);
}


