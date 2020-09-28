#ifndef GUIDER_FOLLOW_H
#define GUIDER_FOLLOW_H

#include "ros/ros.h"

#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "laserScan.h"
#include "tf2_msgs/TFMessage.h"

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
    void poseCallback(const tf2_msgs::TFMessageConstPtr &msg);
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
    bool initial_scan_;
    tf2_msgs::TFMessageConstPtr pose_fetch_;

    struct Marker
    {
        geometry_msgs::Vector3Stamped pose;
        double threshold_distance;
        double shortest_dist;
        bool detected;
        bool reached;
    };
    Marker marker_;

    ros::Time start_time_;   //!< start time
    ros::Duration duration_; //!< duration since start time (seconds)
};

#endif // GUIDER_FOLLOW_H