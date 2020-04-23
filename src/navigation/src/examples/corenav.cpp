#include "mavros_communicator.h"
#include "corenav.h"

/*
  This is an example file. It is a demonstration of how to build navigation functions using mavros_publisher
  1) include "mavros_publisher.h"
  2) include this file's header file
 */

int yawChannel = 4;
int rollChannel = 2;
int pitchChannel = 1;
int throttleChannel = 3;
int lateralhannel = 6;
int forwardChannel = 5;

void yaw(int pwm) {
  publisher(yawChannel, pwm);
}

void roll(int pwm) {
  publisher(rollChannel, pwm);
}

void pitch(int pwm) {
  publisher(pitchChannel, pwm);
}

void throttle(int pwm) {
  publisher(throttleChannel, pwm);
}

void forward(int pwm) {
  publisher(forwardChannel, pwm);
}

void lateral(int pwm) {
  publisher(strafeChannel, pwm);
}
