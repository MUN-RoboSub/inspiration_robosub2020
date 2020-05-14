#ifndef RC_PUBLISHER_H
#define RC_PUBLISHER_H

#include "ros/ros.h"
#include "mavros_msgs/OverrideRCIn.h"

void rc_raw(int channel, int pwm);
void rc(int channel, float pwm);
enum RCCHANNEL {
  PITCH_CHNL,
  ROLL_CHNL,
  THROTTLE_CHNL,
  YAW_CHNL,
  FORWARD_CHNL,
  LATERAL_CHNL,
  CAMERAPAN_CHNL,
  CAMERATILT_CHNL,
  LIGHTS1_CHNL,
  LIGHTS2_CHNL,
  VIDEOSWITCH_CHNL,
};

#endif
