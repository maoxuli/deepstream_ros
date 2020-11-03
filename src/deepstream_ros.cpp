#include "deepstream_ros.h"
#include "ros_parameter.hpp"

deepstream_ros::deepstream_ros(const ros::NodeHandle& nh, 
                               const ros::NodeHandle& private_nh) 
: _nh(nh)
, _private_nh(private_nh)
{
    try {
        std::string obj_topic = "objects"; 
        ROS_INFO_STREAM("Advertise objects topic: " << obj_topic);
        _obj_pub = _nh.advertise<std_msgs::String>(obj_topic, 2);
    }
    catch (const ros::Exception& ex) {
        ROS_ERROR_STREAM("ROS exception: " << ex.what());
        throw; 
    }

    try {
        _stop = false; 
        ROS_INFO_STREAM("Start deepstream thread...");
        _ds_thread = boost::thread(boost::bind(&deepstream_ros::ds_thread, this));
    } 
    catch (std::exception& ex) {
        ROS_ERROR_STREAM("Boost thread exception: " << ex.what());
        throw; 
    }
}

deepstream_ros::~deepstream_ros() 
{
    if (_ds_thread.joinable()) { 
        _stop = true; 
        _ds_thread.join();
    } 
}

// thread function for deepstream pipeline 
void deepstream_ros::ds_thread() 
{  
    ROS_INFO("DeepStream thread start");

    while (!_stop && ros::ok()) 
    {

    }

    ROS_INFO("DeepStream thread stopped!");
}
