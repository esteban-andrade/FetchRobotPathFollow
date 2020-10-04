/**
 * @file laserScan.h
 * @author Esteban Andrade
 * @brief 
 * @version 0.1
 * @date 2020-10-04
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DETECTCABINET_H
#define DETECTCABINET_H

#include <sensor_msgs/LaserScan.h>

class LaserDetection
{
private:
  double laser_reading_; 
public:
 
  LaserDetection();
 
  bool detectObtacle(sensor_msgs::LaserScan::ConstPtr laserScan);
  
  double getLaserReading(sensor_msgs::LaserScan::ConstPtr laserScan);
};

#endif // DETECTCABINET_H