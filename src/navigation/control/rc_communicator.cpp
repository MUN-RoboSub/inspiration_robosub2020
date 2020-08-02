#include "control/rc_communicator.h"
#include "control/publishers.h"
#include "control/subscribers.h"
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

void imuTurn(int tgtHeading, float speed)
{
    // re-implement this later
    if(tgtHeading > compassHdg) {
	if ((tgtHeading - compassHdg) > 180)
	    speed = speed * -1;
    } else if (tgtHeading < compassHdg) {
	if ((compassHdg - tgtHeading) < 180)
	    speed = speed * -1;
    }
    
    while(!(compassHdg < (tgtHeading + 1) && compassHdg > (tgtHeading - 1))) {
	rc(YAW_CHNL, speed);
	ROS_INFO("%f", compassHdg);
	usleep(1000);
    }
    ROS_INFO("%f", compassHdg);
    rc(YAW_CHNL, 0);
}
