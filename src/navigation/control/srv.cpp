#include "ros/ros.h"
#include "control/srv.h"
#include "control/messages.h"

ros::ServiceClient arming_client;
ros::ServiceClient mode_client;

void initSrv(ros::NodeHandle *n){
  arming_client = n->serviceClient<mavros_msgs::CommandBool>
    ("mavros/cmd/arming");
  mode_client = n->serviceClient<mavros_msgs::SetMode>
    ("mavros/set_mode");
}
