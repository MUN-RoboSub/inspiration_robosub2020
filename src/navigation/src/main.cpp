#include "ros/ros.h"
#include <vector>

#include "navigation/CVarray.h"
#include "mavros_communicator.h"
#include "yaw.h"
#include "rccv.h"

// declare publishers and subscribers
ros::Publisher rc_pub; 
ros::Subscriber finalgate_sub;

// global variables
std::vector<long int> finalgateCoords;

void finalgateCallback(const navigation::CVarray::ConstPtr& msg){
  finalgateCoords = msg->array;
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
  
  ros::Rate loop_rate(10);
  while(ros::ok()){
    rc_if_cv(4, 1900);
    loop_rate.sleep();
  }
  
  return 0;
}
