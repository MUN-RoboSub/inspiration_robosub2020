#include <iostream>
#include rc_communicator.h
/**
This file has the function to move the sub at a certain velocity (m/s)
*/
double kP = 0.65;
//needs to be tuned!

double speed_delta;
double clipped_speed;
double upperBound = 1;
double adjSpeed = 0;
double currentSpeed = 1500;

float clip(float n, float lower, float upper) {
  return std::max(lower, std::min(n, upper));
}

void velocityMove(int directionChannel, double targetSpeed, double currentSpeed) {
    speed_delta = (targetSpeed-currentSpeed)*kP;
    clipped_speed = 400*(clip(speed_delta, -upperBound, upperBound));
    adjSpeed = currentSpeed + clipped_speed;
    
    rc.raw(directionChannel, adjSpeed)
    currentSpeed = adjSpeed;
    //add a ROS_OUT of the speed in the desired direction for debug purposes.
}


