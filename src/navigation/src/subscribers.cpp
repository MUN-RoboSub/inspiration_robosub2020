#include "ros/ros.h"
#include "subscribers.h"
#include "global_data.h"

ros::Subscriber finalgate_sub;
ros::Subscriber compassHdg_sub;

// callback functions

void finalgateCallback(const navigation::CVarray::ConstPtr& msg){
  finalgateCoords = msg->array;
}
void headingCallback(const std_msgs::Float64::ConstPtr& msg){
  compassHdg = msg->data;
}
