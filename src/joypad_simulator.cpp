#include "joypad_simulator.hh"
#define CTRL_C 3
#define Q_ASCII 113

void JoyPadSimulator::Prepare()
{
    // button map key is the ascii code of the char, value is the position in button array
    buttonMap[int('a')] = 0;
    buttonMap[int('s')] = 1;
    buttonMap[int('d')] = 2;
    
   // publish on the topic joy
    pub = nodeHandle.advertise<sensor_msgs::Joy>("joy", 10);
}

void JoyPadSimulator::RunPeriodically()
{
    int c = 0;
    setupTerminal();
    printMenu();
    while(ros::ok() && c!=Q_ASCII && c!=CTRL_C){
      sensor_msgs::Joy msg;
      // init arrays of axes and buttons
      msg.axes.push_back(0);
      msg.axes.push_back(0);
      msg.axes.push_back(0);
      msg.axes.push_back(0);
      
      std::map<int,int>::iterator mapItr;
      // reserve a button for each button in button map
      for(mapItr=buttonMap.begin();mapItr!= buttonMap.end();mapItr++){
	msg.buttons.push_back(0);
      }
      
      // init header
      msg.header.stamp= ros::Time().now();
      
      // get character
      c = getch();
      
      // switch on arrow
      switch (c){
	case KEY_LEFT:
	  msg.axes[3] = -1;
	  printw("Angular velocity left\n");
	  break;
	case KEY_RIGHT:
	   msg.axes[3] = 1;
	    printw("Angular velocity right\n");
	   break;
	case KEY_UP:
	   printw("Linear velocity forward\n");
	   msg.axes[1] = 1;
	   break;
	case KEY_DOWN:
	   printw("Linear velocity backward\n");
	   msg.axes[1] = -1;
	   break;
	  };
	
      
      // try get a button
      try{
	msg.buttons.at(buttonMap.at(c))=1;
      }catch (const std::out_of_range& oor) {
	
      };
      
      // print
      refresh();
      
      // publish message
      pub.publish(msg);
      
    }
    
   // restore terminal normal mode
    restoreTerminal();
    
    // print ctrl c
    if(c==CTRL_C || c==Q_ASCII){
      std::cout <<" Quit \n\n";
    }
}

void JoyPadSimulator::setupTerminal(){
  // init functions
  initscr();
  // get functions and arrow
  keypad(stdscr,true);
  // do not wait enter
  raw();
  //cbreak();
  // do not print characters on terminal
  noecho();
  
}



void JoyPadSimulator::restoreTerminal(){
  // reset terminal normal mode
   endwin();
}

void JoyPadSimulator::printMenu()
{
  printw("Welcome to JoyPad Simulator node\n");
  printw("Supported Keys:\n");
  printw("\t-\tLeft, Right, Up, Down arrows for velocities\n");
  printw("\t-\t a,s,d buttons\n\n");
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "joypad_simulator");
  JoyPadSimulator mNode;
   
  mNode.Prepare();
  //mNode.RunContinuously();
  mNode.RunPeriodically();
  
  return (0);
}


