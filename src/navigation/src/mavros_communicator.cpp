#include "mavros_communicator.h"
#include "main.h"

void publisher(int channel, int pwm) {
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel-1] = pwm;

  rc_pub.publish(msg);
}
