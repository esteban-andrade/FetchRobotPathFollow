/**
 * @file guider_follow.h
 * @author Ajal Singh
 * @brief Fetch robot follows the guider robot by a distance of 1m
 * @version 0.1
 * @date 2020-10-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GUIDER_FOLLOW_H
#define GUIDER_FOLLOW_H

#include "ros/ros.h"

#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "tf2_msgs/TFMessage.h"
#include "laserScan.h"
#include <cmath>
#include <chrono>
#include <vector>

class GuiderFollow
{
public:
    GuiderFollow(ros::NodeHandle nh);
    ~GuiderFollow();

    void markerCallback(const geometry_msgs::Vector3StampedPtr &msg);
    void laserCallBack(const sensor_msgs::LaserScanConstPtr &msg);
    void stop();

private:
    ros::NodeHandle nh_;

    ros::Subscriber marker_sub_;
    ros::Subscriber laser_sub_;
    ros::Publisher vel_pub_;
    geometry_msgs::Twist twistMsg_;
    ros::Subscriber pose_tracker_;

    LaserDetection laserDetection_;

    double laser_readings_;
    bool obstacle_detected_;
    bool obstacle_reported_;
    bool search_reported_;
    bool sweep_complete_;
    tf2_msgs::TFMessageConstPtr pose_fetch_;

    struct Marker
    {
        geometry_msgs::Vector3Stamped pose;
        double threshold_distance;
        const double head_2_base_offset = 0.1088;
        double shortest_dist;
        bool detected;
        bool reached;
    };
    Marker marker_;

    ros::Time start_time_;   //!< start time
    ros::Duration duration_; //!< duration since start time (seconds)
};

#endif // GUIDER_FOLLOW_H