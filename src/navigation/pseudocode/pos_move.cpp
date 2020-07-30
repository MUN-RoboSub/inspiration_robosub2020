#include <iostream>
#include <cmath> 
#include rc_communicator.h

double kP = 0.5;
//needs to be tuned!
double distMoved = 0;
double error;
double speed;
double THRESHOLD = 0.1;
double originHeading = 0;

void pos_move_dvl(int directionChannel, double initPos, double tgtDistanceMoved, double currentPosition) {
    //NOTE: while the other function needed both x and y, this function only needs the position of the direction 
    //we are moving in, so if we're moving straight (which we will 99% of the time), then use y!
    
    distMoved = currentPosition - initPos;
    error = tgtDistanceMoved - distMoved;
    speed = 1500 + (400*kp*error);
    
    while(abs(error) > 0.1) {
        rc.raw(directionChannel, adjSpeed)
        currentSpeed = adjSpeed;
        //add a ROS_OUT of the position for debug purposes!
        //also, make sure theres a "while program active" in loop so it can be killed if needed
        
        distMoved = currentPosition - initPos;
        error = tgtDistanceMoved - distMoved;
        speed = 1500 + (400*kp*error);
    }
    
}

void turnToTarget(double originalHeading, double targetPosX, double targetPosY, double currentPosX, double currentPosY) {
    double relativeDelta = atan((targetPosY-currentPosY)/(targetPosX-currentPosX));
    double targetAngle = originHeading - relativeDelta;
    //assumes turning right is positive; left negative
    
    imu_turn(targetAngle);
    //repurpose an old IMU turn, I guess.
}