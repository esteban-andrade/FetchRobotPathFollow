#ifndef ROBOT_TELEOP_JOY_H
#define ROBOT_TELEOP_JOY_H

#include "ros/ros.h"

#include <thread>

#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float32.h"


class RobotTeleopJoy
{
public:

    RobotTeleopJoy(ros::NodeHandle nh);
    ~RobotTeleopJoy();

    void joyCallback(const sensor_msgs::JoyPtr &msg);

    void velocityPublisher();

private:
    ros::NodeHandle nh_;  
    
    ros::Subscriber joy_sub_;
    ros::Publisher vel_pub_;
    geometry_msgs::Twist twistMsg_; 
};


#endif // ROBOT_TELEOP_JOY_H