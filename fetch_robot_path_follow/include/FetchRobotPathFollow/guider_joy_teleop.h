/**
 * @file guider_joy_teleop.h
 * @author Ajal Singh
 * @brief Allows joystick control of /cmd_vel subscribers
 * @version 0.1
 * @date 2020-10-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef GUIDER_JOY_TELEOP_H
#define GUIDER_JOY_TELEOP_H

#include "ros/ros.h"

#include <thread>

#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"


class GuiderJoyTeleop
{
public:

    GuiderJoyTeleop(ros::NodeHandle nh);
    ~GuiderJoyTeleop();

    void joyCallback(const sensor_msgs::JoyPtr &msg);

    void velocityPublisher();

private:
    ros::NodeHandle nh_;  
    
    ros::Subscriber joy_sub_;
    ros::Publisher vel_pub_;
    geometry_msgs::Twist twistMsg_; 
};


#endif // GUIDER_JOY_TELEOP_H