#include "../include/FetchRobotPathFollow/guider_follow.h"

GuiderFollow::GuiderFollow(ros::NodeHandle nh)
    : nh_(nh)
{
  marker_sub_ = nh_.subscribe("/aruco_single/position", 1000, &GuiderFollow::markerCallback, this);
  laser_sub_ = nh_.subscribe("/base_scan_raw", 100, &GuiderFollow::laserCallBack, this);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  marker_.threshold_distance = 1.0 - marker_.head_2_base_offset;
  ROS_INFO_STREAM("init");

  duration_ = start_time_ - start_time_;

  sweep_complete_ = false;
  obstacle_reported_ = false;
  search_reported_ = false;
}

GuiderFollow::~GuiderFollow()
{
}

void GuiderFollow::markerCallback(const geometry_msgs::Vector3StampedPtr &msg)
{
  // inform user of guider dtection
  if (!marker_.detected)
  {
    marker_.detected = true;
    search_reported_ = false;
    ROS_INFO_STREAM("Guider Detected!");
    sweep_complete_ = false;
  }

  // convert marker to pose to robot's ref. frame & calc distance
  marker_.pose.vector.x = msg->vector.z;
  marker_.pose.vector.y = msg->vector.x;
  marker_.pose.vector.z = msg->vector.y;

  marker_.shortest_dist = roundf64(sqrt(pow(marker_.pose.vector.x, 2) + pow(marker_.pose.vector.y, 2)) * 10) / 10;

  // Maintain 1m distance between robot and guider
  if (marker_.shortest_dist <= (marker_.threshold_distance + 0.01) && marker_.shortest_dist >= (marker_.threshold_distance - 0.01))
  {
    twistMsg_.linear.x = 0;
    twistMsg_.angular.z = 0;
    if (!marker_.reached)
    {
      ROS_INFO_STREAM("Guider is stationary");
      marker_.reached = true;
    }
  }

  // Adjust linear and angular velocity to attempt to maintain a 1m gap
  else
  {
    marker_.reached = false;
    if (!obstacle_detected_)
    {
      // proportional control for linear velocity
      double error = marker_.shortest_dist - marker_.threshold_distance;

      // Move forwards or backwards
      if (marker_.shortest_dist > marker_.threshold_distance * 1.5)
      {
        twistMsg_.linear.x = error;
      }
      else if (marker_.shortest_dist < marker_.threshold_distance * 0.95)
      {
        twistMsg_.linear.x = -0.3;
      }
      else
      {
        twistMsg_.linear.x = error / 2;
      }

      // Turn left or right
      if (marker_.pose.vector.y == 0)
      {
        twistMsg_.angular.z = 0;
      }
      else
      {
        twistMsg_.angular.z = -marker_.pose.vector.y;
      }
      obstacle_reported_ = false;
    }
  }
  vel_pub_.publish(twistMsg_);

  // Start timing
  start_time_ = ros::Time::now();
}

void GuiderFollow::laserCallBack(const sensor_msgs::LaserScanConstPtr &msg)
{
  obstacle_detected_ = laserDetection_.detectObtacle(msg);
  laser_readings_ = laserDetection_.getLaserReading(msg);
  //ROS_INFO_STREAM(laser_readings_);

  if (obstacle_detected_)
  {
    if (marker_.detected)
    {
      if (!obstacle_reported_)
      {
        ROS_INFO_STREAM("Obstacle blocking path. Stopped following");
        obstacle_reported_ = true;
      }
      twistMsg_.angular.z = 0;
      twistMsg_.linear.x = 0;
    }
    else
    {
      if (!obstacle_reported_)
      {
        ROS_INFO_STREAM("Obstacle detected");
        obstacle_reported_ = true;
      }
      twistMsg_.angular.z = 0;
      twistMsg_.linear.x = -2.0;
    }

    vel_pub_.publish(twistMsg_);
  }

  if (!obstacle_detected_)
  {
    obstacle_reported_ = false;
  }
}

void GuiderFollow::stop()
{
  while (ros::ok)
  {
    //reset duration timer
    if (duration_ > ros::Duration(20.0))
    {
      start_time_ = ros::Time::now();
    }

    duration_ = ros::Time::now() - start_time_;

    // Search for guider clockwise
    if (duration_ >= ros::Duration(2.0) && duration_ <= ros::Duration(8.0) && !marker_.detected && !sweep_complete_)
    {
      twistMsg_.angular.z = -1.57;
      twistMsg_.linear.x = 0.0;
      vel_pub_.publish(twistMsg_);
      if (!search_reported_)
      {
        ROS_INFO_STREAM("Searching for guider");
        search_reported_ = true;
      }
    }

    // Search for guider anti-clockwise
    if (duration_ > ros::Duration(8.0) && duration_ <= ros::Duration(14.0) && !marker_.detected && !sweep_complete_)
    {
      twistMsg_.angular.z = 1.57;
      twistMsg_.linear.x = 0.0;
      vel_pub_.publish(twistMsg_);
    }

    // Report no guider detected
    if (duration_ == ros::Duration(14.0) && !marker_.detected && !sweep_complete_)
    {
      sweep_complete_ = true;
      search_reported_ = false;
      ROS_INFO_STREAM("No Guider detected. Cease searching");
    }

    if (duration_ >= ros::Duration(3.0) && marker_.detected)
    {
      ROS_INFO_STREAM("No Guider detected. Stopping Operation");

      marker_.detected = false;
      sweep_complete_ = false;
      start_time_ = ros::Time::now();
    }
  }
}