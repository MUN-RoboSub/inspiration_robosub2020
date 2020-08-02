#include "ros/ros.h"
#include "control/subscribers.h"
#include "control/messages.h"
#include <cmath>
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
    compassHdg_sub = n->subscribe("/gazebo/model_states", 1000, headingCallback);
}

void initSimSubs(ros::NodeHandle *n){
    gazeboModelStates_sub = n->subscribe("/gazebo/model_states", 1000, gazeboModelStatesCallback);
}

// callback functions
void finalgateCallback(const navigation::CVarray::ConstPtr& msg){
    finalgateCoords = msg->array;
}
void headingCallback(const gazebo_msgs::ModelStates::ConstPtr& msg){
    geometry_msgs::Pose position;
    position = msg->pose[1];
    float angle = 2 * acos(position.orientation.w);
    float s = sqrt(1-(pow(position.orientation.w, 2)));
    float raw_yaw = (s > 0.0001) ? position.orientation.z/s : position.orientation.z;
    float headingRadians = raw_yaw * angle;
    compassHdg = headingRadians * (180/3.141592);
    if(compassHdg < 0) {
	compassHdg = compassHdg * -1;
    } else {
	compassHdg = 360 - compassHdg;
    }
}
void gazeboModelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr& msg){
    gazeboTwist = msg->twist[1];
    gazeboPose = msg->pose[1];
}
