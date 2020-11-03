#include <ros/ros.h>
#include "deepstream_ros.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "deepstream_ros");
    ros::NodeHandle nh, private_nh("~"); 
    deepstream_ros ds_ros(nh, private_nh); 
    ros::spin(); 
    return 0;
}
