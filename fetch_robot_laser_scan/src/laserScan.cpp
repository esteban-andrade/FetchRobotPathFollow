#include "laserScan.h"

static const int LASER_FIELD_OF_VIEW = 120;
static const double LASER_LIMIT = 0.15;
static const double RAD_ROBOT = 0.257;

LaserDetection::LaserDetection()
{
}

bool LaserDetection::detectObtacle(sensor_msgs::LaserScan::ConstPtr laserScan)
{
    double laser_reading = laserScan->range_max;                                  // get max reading
    int range_start = (laserScan->ranges.size() / 2) - (LASER_FIELD_OF_VIEW / 2); // consider star of FOV
    int range_end = (laserScan->ranges.size() / 2) + (LASER_FIELD_OF_VIEW / 2);   //consider end of FOV
    for (unsigned int i = range_start; i <= range_end; i++)
    {
        if (laserScan->ranges.at(i) < laser_reading)
        {
            laser_reading = laserScan->ranges.at(i); // Store laser reading
        }
    }
    if (laser_reading <= LASER_LIMIT + RAD_ROBOT) // check if condition is valid
    {
        return false;
    }
    else
    {
        return true;
    }
}

double LaserDetection::getLaserReading(sensor_msgs::LaserScan::ConstPtr laserScan)
{
    int range_start = (laserScan->ranges.size() / 2) - (LASER_FIELD_OF_VIEW / 2);
    int range_end = (laserScan->ranges.size() / 2) + (LASER_FIELD_OF_VIEW / 2);
    for (unsigned int i = range_start; i <= range_end; i++)
    {
        if (laserScan->ranges.at(i) < laser_reading_)
        {
            laser_reading_ = laserScan->ranges.at(i);
        }
    }
    return laser_reading_;
}