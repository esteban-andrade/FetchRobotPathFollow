#ifndef GUIDER_FOLLOW_H
#define GUIDER_FOLLOW_H

#include "ros/ros.h"

#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/Twist.h"

#include <cmath>

class GuiderFollow
{
public:
    GuiderFollow(ros::NodeHandle nh);
    ~GuiderFollow();

    void markerCallback(const geometry_msgs::Vector3StampedPtr &msg);

private:
    ros::NodeHandle nh_;  
    
    ros::Subscriber marker_sub_;
    ros::Publisher vel_pub_;
    geometry_msgs::Twist twistMsg_;
    
    double threshold_distance_;
};

#endif // GUIDER_FOLLOW_H