#ifndef __DEEPSTREAM_ROS_H__
#define __DEEPSTREAM_ROS_H__

#include <ros/ros.h>
#include <std_msgs/Trigger.h>

#include <boost/thread.hpp>
#include <mutex>
#include <atomic>

class videocapture_ros
{
public: 
    videocapture_ros(const ros::NodeHandle& nh = ros::NodeHandle(), 
                  const ros::NodeHandle& private_nh = ros::NodeHandle("~")); 

    ~videocapture_ros(); 


private: 
    ros::NodeHandle _nh; 
    ros::NodeHandle _private_nh; 

private: 
    boost::thread _gst_thread;
    std::atomic<bool> _stop; 
    std::mutex _mutex; 

    void gst_thread(); 
}; 

#endif 
