#include "ros/ros.h"

#include "init.h"
#include "rc_communicator.h"
#include "global_data.h"

int main(int argc, char **argv){
  //initialize the node
  ros::init(argc, argv, "main_mavros"); 
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

  ros::Rate loop_rate(10);
  while(ros::ok()){
      rc(FORWARD_CHNL, 1);
      //ROS_INFO("x: %f", gazeboPose.position.x);
      loop_rate.sleep();
  }
  
  disarm();
  return 0;
}
