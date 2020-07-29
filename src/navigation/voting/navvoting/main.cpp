#include "ros/ros.h"
#include "voting/subscribers.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "navvoting");
    ros::NodeHandle n;

    // initSubs(&n);

    ros::Rate loop_rate(20);
    while(ros::ok()){
      
    }
    
}
