#include "ros/ros.h"
#include <vector>
#include "voting/subscribers.h"
#include "voting/messages.h"

/*
  Store/initialize all ROS subscribers
 */

// subscribers
ros::Subscriber sub_cvGatePos;
ros::Subscriber sub_cvBuoyPos;
ros::Subscriber sub_dvlPos;

// variables that store subscriber data when a topic is published to
std::vector<long int> cvGatePos;
std::vector<long int> cvBuoyPos;
std::vector<double> dvlPos;

void initSubs(ros::NodeHandle *n)
{
    sub_cvGatePos = n->subscribe("/auvPos/cv/gate", 1000, cvGateCallback);
    sub_cvBuoyPos = n->subscribe("/auvPos/cv/buoy", 1000, cvBuoyCallback);
    sub_dvlPos = n->subscribe("/auvPos/dvl/pos", 1000, dvlPosCallback);
}

// callback functions
void cvGateCallback(const navigation::CVarray::ConstPtr& msg)
{
    cvGatePos = msg->array;
}
void cvBuoyCallback(const navigation::CVarray::ConstPtr& msg)
{
    cvBuoyPos = msg->array;
}
void dvlPosCallback(const navigation::floatarray::ConstPtr& msg)
{
  dvlPos = msg->array;
}
