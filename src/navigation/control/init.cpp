#include "ros/ros.h"
#include "control/messages.h"
#include "control/srv.h"

void arm(){
  mavros_msgs::CommandBool arm_cmd;
  arm_cmd.request.value = true;

  if(arming_client.call(arm_cmd) && arm_cmd.response.success)
    ROS_INFO("Armed successfully");
}

void disarm(){
  mavros_msgs::CommandBool arm_cmd;
  arm_cmd.request.value = false;

  if(arming_client.call(arm_cmd) && arm_cmd.response.success)
    ROS_INFO("Disarmed successfully");
}
