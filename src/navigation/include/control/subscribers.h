#ifndef SUBSCRIBERS_H
#define SUBSCRIBERS_H
#include "control/messages.h"

extern ros::Subscriber finalgate_sub;
extern ros::Subscriber compassHdg_sub;
extern ros::Subscriber gazeboModelStates_sub;

extern std::vector<long int> finalgateCoords;
extern float compassHdg;
extern geometry_msgs::Twist gazeboTwist;
extern geometry_msgs::Pose gazeboPose;

void initSubs(ros::NodeHandle *n);
void initSimSubs(ros::NodeHandle *n);

void finalgateCallback(const navigation::CVarray::ConstPtr& msg);
void headingCallback(const gazebo_msgs::ModelStates::ConstPtr& msg);
void gazeboModelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr& msg);

#endif
