#ifndef SUBSCRIBERS_H
#define SUBSCRIBERS_H

#include "voting/messages.h"

extern ros::Subscriber sub_cvGatePos;
extern ros::Subscriber sub_cvBuoyPos;
extern ros::Subscriber sub_dvlPos;

extern std::vector<long int> cvGatePos;
extern std::vector<long int> cvBuoyPos;
extern std::vector<double> dvlPos;

void initSubs(ros::NodeHandle *n);
void cvGateCallback(const navigation::CVarray::ConstPtr& msg);
void cvBuoyCallback(const navigation::CVarray::ConstPtr& msg);
void dvlPosCallback(const navigation::floatarray::ConstPtr& msg);

#endif
