#include <ros/ros.h>
#include "videocapture_ros.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "videocapture");
    ros::NodeHandle nh, private_nh("~"); 
    videocapture_ros videocapture(nh, private_nh); 
    ros::spin(); 
    return 0;
}
