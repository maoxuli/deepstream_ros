#include "deepstream_ros.h"
#include "ros_parameter.hpp"
// #include "deepstream_app_main.h"

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

    LoadParam(_private_nh, "config", _config_file, true); 

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

extern "C" {
    int ds_main(int argc, char *argv[]); 
}

// thread function for deepstream pipeline 
void deepstream_ros::ds_thread() 
{  
    ROS_INFO("DeepStream thread start");

    std::vector<std::string> args;
    args.push_back("deepstream-ros"); 
    args.push_back("-c"); 
    args.push_back(_config_file);
    
    std::vector<char*> argv;
    for (const auto& arg : args)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    ds_main(argv.size()-1, argv.data()); 

    ROS_INFO("DeepStream thread stopped!");
}
