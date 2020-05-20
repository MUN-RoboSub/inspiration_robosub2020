#ifndef INIT_H
#define INIT_H
#include "ros/ros.h"

void initSubs(ros::NodeHandle *n);
void initPubs(ros::NodeHandle *n);
void initSrv(ros::NodeHandle *n);

void arm();
void disarm();

#endif
