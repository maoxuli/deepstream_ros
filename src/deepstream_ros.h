#ifndef __DEEPSTREAM_ROS_H__
#define __DEEPSTREAM_ROS_H__

#include <ros/ros.h>
#include <std_msgs/String.h>

#include <boost/thread.hpp>
#include <mutex>
#include <atomic>

class deepstream_ros
{
public: 
    deepstream_ros(const ros::NodeHandle& nh = ros::NodeHandle(), 
                  const ros::NodeHandle& private_nh = ros::NodeHandle("~")); 

    ~deepstream_ros(); 


private: 
    ros::NodeHandle _nh; 
    ros::NodeHandle _private_nh; 
    ros::Publisher _obj_pub; 

private: 
    boost::thread _ds_thread;
    std::atomic<bool> _stop; 
    std::mutex _mutex; 

    void ds_thread(); 

    std::string _config_file; 
}; 

#endif 
