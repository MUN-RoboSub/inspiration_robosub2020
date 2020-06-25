#ifndef SUBSCRIBERS_H
#define SUBSCRIBERS_H
#include "messages.h"

extern ros::Subscriber finalgate_sub;
extern ros::Subscriber compassHdg_sub;
extern ros::Subscriber gazeboTwist_sub;

void finalgateCallback(const navigation::CVarray::ConstPtr& msg);
void headingCallback(const std_msgs::Float64::ConstPtr& msg);
void gazeboTwistCallback(const gazebo_msgs::ModelStates::ConstPtr& msg);

#endif
