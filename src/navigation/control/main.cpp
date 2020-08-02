#include "ros/ros.h"
#include <cmath>

#include "control/init.h"
#include "control/rc_communicator.h"
#include "control/subscribers.h"
#include "control/publishers.h"
#include "control/srv.h"

/* parameters: target x and target y */
void navToPos(double x, double y)
{
    float heading;
    float initheading; /* initial heading */
    float xDiff, yDiff;
    /* calculate the difference between the current and target positions */
    xDiff = x - gazeboPose.position.x;
    yDiff = y - gazeboPose.position.y;

    ROS_INFO("%f %f", xDiff, yDiff);
    // yes i am trying to kill your eyes: the following condition checks whether xDiff and yDiff are positive, and then converts it to a positive value if it's negative, and then sees if the difference is low enough to stop the loop
    while(ros::ok() && ((xDiff > 0) ? xDiff : -xDiff) > 0.2 && ((yDiff > 0) ? yDiff : -yDiff) > 0.2) {
	xDiff = x - gazeboPose.position.x;
	yDiff = y - gazeboPose.position.y;

	/* angle is the inverse tangent of the differences */
	heading = atan(xDiff/yDiff) * (180/3.141592);
	initheading = heading;
	/* correct the angle to fit in line with the absolute degree system */
	if(xDiff > 0) {
	    heading = (yDiff > 0) ? 270 + heading : 90 + heading;
	} else {
	    heading = (yDiff > 0) ? 270 + heading : 180 - (90 - heading);
	}

	ROS_INFO("%f %f", heading, initheading);
	/* turn to the correct heading and go forward in a loop */
	imuTurn(heading, 0.8);
	rc(FORWARD_CHNL, 1);
	usleep(1000);
    }
    
    rc(FORWARD_CHNL, 0);
}

int main(int argc, char **argv)
{
  //initialize the node
  ros::init(argc, argv, "main_control"); 
  ros::NodeHandle n;

  // async spinner to update subscribers
  ros::AsyncSpinner spinner(4);
  spinner.start();

  // initialize and arm
  initSubs(&n);
  initSimSubs(&n);
  initPubs(&n);
  initSrv(&n);
  arm();

  // sleep so that the spinner has time to update the data values
  sleep(5);

  ros::Rate loop_rate(20);
  /* while(ros::ok()){
      //rc(FORWARD_CHNL, 0.2);
      rcTime(LATERAL_CHNL, 0.2, 4);
      //ROS_INFO("x: %f", gazeboPose.position.x);
      loop_rate.sleep();
      } */
  /*  
  while(ros::ok()){
    
    if(!finalgateCoords.empty()){
      if(finalgateCoords[1] > 0) {
	rc(LATERAL_CHNL, 0.3);
	printf("right\n");
      } else if (finalgateCoords[1] < 0) {
	rc(LATERAL_CHNL, -0.3);
	printf("left\n");
      }
    }

    loop_rate.sleep();
  }
  */
  navToPos(2, -5);
  navToPos(4, -3);
  navToPos(6, -5);
  navToPos(4, -7);

  disarm();
  return 0;
}
