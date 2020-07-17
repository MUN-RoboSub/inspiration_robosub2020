#include "rc_communicator.h"
#include "publishers.h"
#include <ctime>

/*
  RC-publishing functions
 */

void rc_raw(int channel, int pwm) {
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel] = pwm;
  rc_pub.publish(msg);
}

void rc(int channel, float speed){
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel] = 1500.0 + (speed*400.0); // pwm 1100 is lowest, pwm 1900 is highest
  rc_pub.publish(msg);
}

void rcTime(int channel, float speed, int seconds){

    time_t endTime = time(NULL) + seconds;
    while(time(NULL) < endTime){
	rc(channel, speed);
	usleep(1000);
    }

    rc(channel, 0);
}
