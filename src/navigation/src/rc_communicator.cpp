#include "rc_communicator.h"
#include "main.h"

/*
  RC-publishing functions
 */

void rc_raw(int channel, int pwm) {
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel] = pwm;
  rc_pub.publish(msg);
}

void rc(int channel, int speed){
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel] = 1500 + (speed*400); // pwm 1100 is lowest, pwm 1900 is highest
  rc_pub.publish(msg);
}
