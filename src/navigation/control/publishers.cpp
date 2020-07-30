#include "ros/ros.h"
#include "control/publishers.h"
#include "control/messages.h"

ros::Publisher rc_pub;

void initPubs(ros::NodeHandle *n){
  rc_pub = n->advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 1000);
}
