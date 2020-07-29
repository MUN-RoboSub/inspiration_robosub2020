#include "ros/ros.h"

#include "control/init.h"
#include "control/rc_communicator.h"
#include "control/global_data.h"

int main(int argc, char **argv){
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
  rcTime(FORWARD_CHNL, 0.5, 4);
  //rcTime(FORWARD_CHNL, 0.7, 10);
  //rcTime(YAW_CHNL, 0.7, 5);
  //rcTime(FORWARD_CHNL, 0.7, 10);
  //rcTime(YAW_CHNL, 0.7, 5);
  //rcTime(FORWARD_CHNL, 0.7, 10);
  //rcTime(YAW_CHNL, 0.7, 5);
  //rcTime(FORWARD_CHNL, 0.7, 10);
  //rcTime(LATERAL_CHNL, 0.7, 10);
  //rcTime(FORWARD_CHNL, -0.7, 10);
  //rcTime(LATERAL_CHNL, -0.7, 10);
  //disarm();
  return 0;
}
