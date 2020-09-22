#ifndef GUIDER_FOLLOW_H
#define GUIDER_FOLLOW_H

#include "ros/ros.h"

#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"

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

class GuiderFollow
{
public:
    GuiderFollow(ros::NodeHandle nh);
    ~GuiderFollow();

    void markerCallback(const geometry_msgs::Vector3StampedPtr &msg);
    void laserCallBack(const sensor_msgs::LaserScanConstPtr &);
    LaserDetection laserDetection_;
    void navigation();

private:
    ros::NodeHandle nh_;

    ros::Subscriber marker_sub_;
    ros::Publisher vel_pub_;
    geometry_msgs::Twist twistMsg_;

    double threshold_distance_;
    double laser_readings_;
    bool obstacle_detected_;
    ros::Subscriber sub1_;
    double shortest_dist_;
    double pose_x_;
    double pose_y_;
    double pose_z_;
};

#endif // GUIDER_FOLLOW_H