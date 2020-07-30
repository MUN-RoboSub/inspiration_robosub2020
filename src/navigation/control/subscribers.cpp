#include "ros/ros.h"
#include "control/subscribers.h"
#include "control/messages.h"

// subscribers
ros::Subscriber finalgate_sub;
ros::Subscriber compassHdg_sub;
ros::Subscriber gazeboModelStates_sub;

// data
std::vector<long int> finalgateCoords;
float compassHdg;
// simulation data
geometry_msgs::Twist gazeboTwist;
geometry_msgs::Pose gazeboPose;

void initSubs(ros::NodeHandle *n){
    finalgate_sub = n->subscribe("finalgate_cv", 1000, finalgateCallback);
    compassHdg_sub = n->subscribe("/mavros/global_position/compass_hdg", 1000, headingCallback);
}

void initSimSubs(ros::NodeHandle *n){
    gazeboModelStates_sub = n->subscribe("/gazebo/model_states", 1000, gazeboModelStatesCallback);
}

// callback functions
void finalgateCallback(const navigation::CVarray::ConstPtr& msg){
    finalgateCoords = msg->array;
}
void headingCallback(const std_msgs::Float64::ConstPtr& msg){
    compassHdg = msg->data;
}
void gazeboModelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr& msg){
    gazeboTwist = msg->twist[1];
    gazeboPose = msg->pose[1];
}
