#include "ros/ros.h"
#include "mavros_communicator.h"
#include "yaw.h"

extern ros::Publisher pub; 
int main(int argc, char **argv) {

  ros::init(argc, argv, "main_mavros"); 

  ros::NodeHandle n;
  pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 1000);
  ros::Rate loop_rate(10);

  while(ros::ok()){
    /* set the pwm value of the yaw channel to 1900 */
    // publisher(4, 1900);
    yaw();
    
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  return 0;

}
