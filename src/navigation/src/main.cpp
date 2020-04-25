#include "ros/ros.h"
#include <vector>

#include "messages.h"
#include "rc_communicator.h"
#include "rccv.h"

// declare publishers and subscribers
ros::Publisher rc_pub; 
ros::Subscriber finalgate_sub;
ros::Subscriber compassHdg_sub;

// global variables
std::vector<long int> finalgateCoords;
float compassHdg;

void finalgateCallback(const navigation::CVarray::ConstPtr& msg){
  finalgateCoords = msg->array;
}
void headingCallback(const std_msgs::Float64::ConstPtr& msg){
  compassHdg = msg->data;
}

int main(int argc, char **argv){
  //initialize the node
  ros::init(argc, argv, "main_mavros"); 
  ros::NodeHandle n;

  // async spinner to update subscribers
  ros::AsyncSpinner spinner(4);
  spinner.start();
  
  // define publishers and subscribers
  rc_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 1000);
  finalgate_sub = n.subscribe("finalgate_cv", 1000, finalgateCallback);
  compassHdg_sub = n.subscribe("/mavros/global_position/compass_hdg", 1000, headingCallback);
  
  ros::Rate loop_rate(10);
  while(ros::ok()){
    rc(THROTTLE_CHNL, -1);
    loop_rate.sleep();
  }
  
  return 0;
}
