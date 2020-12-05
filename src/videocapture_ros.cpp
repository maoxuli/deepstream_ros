#include "videocapture_ros.h"
#include "ros_parameter.hpp"
#include "nvgstcapture/nvgstcapture.h"

videocapture_ros::videocapture_ros(const ros::NodeHandle& nh, 
                                   const ros::NodeHandle& private_nh) 
: _nh(nh)
, _private_nh(private_nh)
{
    try {    
        std::string start_service = "start"; 
        ROS_INFO_STREAM("Advertise start service: " << start_service);

        std::string stop_service = "stop"; 
        ROS_INFO_STREAM("Advertise stop service: " << stop_service);
    }
    catch (const ros::Exception& ex) {
        ROS_ERROR_STREAM("ROS exception: " << ex.what());
        throw; 
    }

    try {
        _stop = false; 
        ROS_INFO_STREAM("Start gstreamer thread...");
        _gst_thread = boost::thread(boost::bind(&deepstream_ros::gst_thread, this));
    } 
    catch (std::exception& ex) {
        ROS_ERROR_STREAM("Boost thread exception: " << ex.what());
        throw; 
    }
}

videocapture_ros::~videocapture_ros() 
{
    if (_gst_thread.joinable()) { 
        _stop = true; 
        _gst_thread.join();
    } 
}

extern "C" {
    int gst_main(int argc, char *argv[]); 
}

// thread function for gstreamer pipeline 
void videocapture_ros::gst_thread() 
{  
    ROS_INFO("GStreamer thread start");

    std::vector<std::string> args;
    args.push_back("videocapture"); 
    
    std::vector<char*> argv;
    for (const auto& arg : args)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    gst_main(argv.size()-1, argv.data()); 

    ROS_INFO("GStreamer thread stopped!");
}
