#include "ros/ros.h"
#include "environmentSensing.h"
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
    ros::init(argc, argv, "laser_scanning");

    ros::NodeHandle nh;
    std::shared_ptr<EnvironmentSensing> pg(new EnvironmentSensing(nh));
    std::thread t1(&EnvironmentSensing::status, pg);

    ros::spin();

    ros::shutdown();

    t1.join();

    return 0;
}