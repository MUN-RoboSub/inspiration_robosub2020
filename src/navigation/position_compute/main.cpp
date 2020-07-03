#include "ros/ros.h"

// message headers
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "gazebo_msgs/ModelStates.h"

/*
UNITS:
- velocity: m/s
- displacement: meters
- frequency: Hz
- time: seconds
 */

// simulation velocity/pose
geometry_msgs::Twist gazeboTwist;
geometry_msgs::Pose gazeboPose;
geometry_msgs::Vector3 velocity;

int dataRecieved = 0;

// for simulation use
void modelStatesCallback(const gazebo_msgs::ModelStates::ConstPtr& msg){
    gazeboTwist = msg->twist[1];
    gazeboPose = msg->pose[1];
    velocity = gazeboTwist.linear;
    dataRecieved = 1;
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    ros::Subscriber modelStatesSub = n.subscribe("/gazebo/model_states", 1000, modelStatesCallback);

    float integratedX = 0;
    float integratedY = 0;
    float integratedZ = 0;
    
    int noSampleCntX = 0;
    int noSampleCntY = 0;
    int noSampleCntZ = 0;
    
    while(!dataRecieved){
	ROS_INFO("recieving no data");
	ros::spinOnce();
    }

    float initialPoseX = gazeboPose.position.x;
    float initialPoseY = gazeboPose.position.y;
    float initialPoseZ = gazeboPose.position.z;
    
    // sleep(3);
    
    ros::Rate loop_rate(1000); // velocity sample rate
    while(ros::ok()){
	
	if(velocity.x == 10){ // 10 is an impossible value, will only be there if no velocity was sampled
	    ROS_INFO("x: no value sampled");
	    ++noSampleCntX;
	} else {
	    integratedX += ((velocity.x * 0.001) * (noSampleCntX + 1));
	    noSampleCntX = 0;
	}
	
	if(velocity.y == 10){
	    ROS_INFO("y: no value sampled");
	    ++noSampleCntY;
	} else {
	    integratedY += ((velocity.y * 0.001) * (noSampleCntY + 1));
	    noSampleCntY = 0;
	}
	
	if(velocity.z == 10){
	    ROS_INFO("z: no value sampled");
	    ++noSampleCntZ;
	} else {
	    integratedZ += ((velocity.z * 0.001) * (noSampleCntZ + 1));
	    noSampleCntZ;
	}
	
	ROS_INFO("\ncalculated displacement -- x: %f | y: %f | z: %f \nactual displacement -- x: %f | y: %f | z: %f \ndisplacement error -- x: %f, | y: %f | z: %f \ninitial position -- x: %f | y: %f | z: %f \ncurrent position -- x: %f | y: %f | z: %f", integratedX, integratedY, integratedZ, (gazeboPose.position.x - initialPoseX), (gazeboPose.position.y - initialPoseY), (gazeboPose.position.z - initialPoseZ), ((gazeboPose.position.x - initialPoseX) - integratedX), ((gazeboPose.position.y - initialPoseY) - integratedY), ((gazeboPose.position.z - initialPoseZ) - integratedZ), initialPoseX, initialPoseY, initialPoseZ, gazeboPose.position.x, gazeboPose.position.y, gazeboPose.position.z);

        velocity.x = 10; // impossible value
	velocity.y = 10;
	velocity.z = 10;
	
	loop_rate.sleep();
	ros::spinOnce();
	
    }
}
