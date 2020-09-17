#ifndef ENVIRONMENTSENSING_H
#define ENVIRONMENTSENSING_H

#include "ros/ros.h"
#include "std_msgs/String.h"
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
#include "sensor_msgs/LaserScan.h"

#include "laserScan.h"

class EnvironmentSensing
{
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub1_;
    double laser_readings_;
    bool obstacle_detected_;
    void laserCallBack(const sensor_msgs::LaserScanConstPtr &);

public:
    //ros::NodeHandle nh_;
    LaserDetection laserDetection_;
    EnvironmentSensing(ros::NodeHandle);
    void status();
};

#endif //ENVIRONMENTSENSING_H