#include "mavros_publisher.h"

ros::Publisher pub;
void publisher(int channel, int pwm) {
  mavros_msgs::OverrideRCIn msg;
  msg.channels[channel-1] = pwm;

  pub.publish(msg);
}
