#include "environmentSensing.h"


EnvironmentSensing::EnvironmentSensing(ros::NodeHandle nh) : nh_(nh)
{
    sub1_ = nh_.subscribe("/base_scan_raw", 10, &EnvironmentSensing::laserCallBack, this);
}


void EnvironmentSensing::status(){
   if (obstacle_detected_==false){
        ROS_INFO_STREAM("Detected  wall");
    } 
}

void EnvironmentSensing::laserCallBack(const sensor_msgs::LaserScanConstPtr &msg)
{
    
    obstacle_detected_ = laserDetection_.detectObtacle(msg);
    laser_readings_ = laserDetection_.getLaserReading(msg);   
}