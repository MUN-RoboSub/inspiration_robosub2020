#include "ros/ros.h"
#include "control/messages.h"

#include "control/publishers.h"
#include "control/subscribers.h"
#include "control/srv.h"

void initSubs(ros::NodeHandle *n){
  finalgate_sub = n->subscribe("finalgate_cv", 1000, finalgateCallback);
  compassHdg_sub = n->subscribe("/mavros/global_position/compass_hdg", 1000, headingCallback);
}

void initSimSubs(ros::NodeHandle *n){
  gazeboModelStates_sub = n->subscribe("/gazebo/model_states", 1000, gazeboModelStatesCallback);
}

void initPubs(ros::NodeHandle *n){
  rc_pub = n->advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 1000);
}

void initSrv(ros::NodeHandle *n){
  arming_client = n->serviceClient<mavros_msgs::CommandBool>
    ("mavros/cmd/arming");
  mode_client = n->serviceClient<mavros_msgs::SetMode>
    ("mavros/set_mode");
}

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
