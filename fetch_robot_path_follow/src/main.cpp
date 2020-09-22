#include "ros/ros.h"
#include "../include/FetchRobotPathFollow/guider_follow.h"
#include <sstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <deque>
#include <mutex>
#include <random>
#include <atomic>
#include <cmath>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "guider_follow");

    ros::NodeHandle nh;
    // std::shared_ptr<EnvironmentSensing> pg(new EnvironmentSensing(nh));
    //std::thread t1(&EnvironmentSensing::status, pg);
    std::shared_ptr<GuiderFollow> robot(new GuiderFollow(nh));
    std::thread vel(&GuiderFollow::navigation, robot);
    ros::spin();

    ros::shutdown();

    // t1.join();
    vel.join();

    return 0;
}