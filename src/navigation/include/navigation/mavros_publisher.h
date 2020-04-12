#ifndef MAVROS_PUBLISHER_H
#define MAVROS_PUBLISHER_H

#include "ros/ros.h"
#include "mavros_msgs/OverrideRCIn.h"

void publisher(int channel, int pwm);

#endif
