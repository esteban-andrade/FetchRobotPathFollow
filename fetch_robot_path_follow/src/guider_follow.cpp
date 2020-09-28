#include "../include/FetchRobotPathFollow/guider_follow.h"

GuiderFollow::GuiderFollow(ros::NodeHandle nh)
    : nh_(nh)
{
  marker_sub_ = nh_.subscribe("/aruco_single/position", 1000, &GuiderFollow::markerCallback, this);
  laser_sub_ = nh_.subscribe("/base_scan_raw", 10, &GuiderFollow::laserCallBack, this);

  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  pose_tracker_ = nh_.subscribe("/tf_static", 10, &GuiderFollow::poseCallback, this);

  marker_.threshold_distance = 1.0;
  ROS_INFO_STREAM("init");

  duration_ = start_time_ - start_time_;
  initial_scan_ = true;
}

GuiderFollow::~GuiderFollow()
{
}

void GuiderFollow::poseCallback(const tf2_msgs::TFMessageConstPtr &msg)
{
  pose_fetch_ = msg;
  //ROS_INFO_STREAM(pose_fetch_->transforms.front());
}
void GuiderFollow::markerCallback(const geometry_msgs::Vector3StampedPtr &msg)
{
  if (!marker_.detected)
  {
    marker_.detected = true;
    ROS_INFO_STREAM("Guider Detected!");
  }

  marker_.pose.vector.x = msg->vector.z;
  marker_.pose.vector.y = msg->vector.x;
  marker_.pose.vector.z = msg->vector.y;

  marker_.shortest_dist = roundf64(sqrt(pow(marker_.pose.vector.x, 2) + pow(marker_.pose.vector.y, 2)) * 10) / 10;

  if (marker_.shortest_dist == marker_.threshold_distance)
  {
    twistMsg_.linear.x = 0;
    twistMsg_.angular.z = 0;
    if (!marker_.reached)
    {
      ROS_INFO_STREAM("Guider is stationary");
      marker_.reached = true;
    }
  }
  else
  {
    marker_.reached = false;
    if (!obstacle_detected_)
    {
      // Move forwards or backwards
      if (marker_.shortest_dist > marker_.threshold_distance * 3)
      {
        twistMsg_.linear.x = 0.3;
      }
      else if (marker_.shortest_dist < marker_.threshold_distance * 0.75)
      {
        twistMsg_.linear.x = -0.3;
      }
      else
      {
        double error = marker_.shortest_dist - marker_.threshold_distance;
        twistMsg_.linear.x = error / 2;
      }

      // Turn left or right
      if (marker_.pose.vector.y > 0.1)
      {
        twistMsg_.angular.z = -0.3;
      }
      else if (marker_.pose.vector.y < -0.1)
      {
        twistMsg_.angular.z = 0.3;
      }
      else if (marker_.pose.vector.y >= -0.1 && marker_.pose.vector.y <= 0.1)
      {
        twistMsg_.angular.z = marker_.pose.vector.y / 8;
      }
      else
      {
        twistMsg_.angular.z = 0;
      }
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
    ROS_INFO_STREAM("Obstacle detected");
    twistMsg_.angular.z = 0;
    twistMsg_.linear.x = -0.3;
    vel_pub_.publish(twistMsg_);

    // Start timing
    start_time_ = ros::Time::now();
  }
}

void GuiderFollow::stop()
{
  while (ros::ok)
  {
    // Check if duration since last checkpoint is > 0.5 secs
    duration_ = ros::Time::now() - start_time_;

    if (initial_scan_ == true)
    {
      auto Start = std::chrono::high_resolution_clock::now();
      if (!marker_.detected)
      {
        auto End = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> Elapsed = End - Start;
        twistMsg_.angular.z = 0.3;
        twistMsg_.linear.x = 0.0;
        if (Elapsed.count() >= 30000.0)
        {
          twistMsg_.angular.z = 0.0;
          twistMsg_.linear.x = 0.0;

          ROS_INFO_STREAM("No Guider detected");
          break;
        }
      }
      else
      {
        ROS_INFO_STREAM("Guider detected");
      }

      initial_scan_ = false;
    }

    if (duration_ >= ros::Duration(3.0) && marker_.detected)
    {
      ROS_INFO_STREAM("No Guider detected. Stopping Operation");

      marker_.detected = false;

      start_time_ = ros::Time::now();
    }
  }
}