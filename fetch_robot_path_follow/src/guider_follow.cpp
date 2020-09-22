#include "../include/FetchRobotPathFollow/guider_follow.h"

GuiderFollow::GuiderFollow(ros::NodeHandle nh)
    : nh_(nh)
{
  marker_sub_ = nh_.subscribe("/aruco_single/position", 1000, &GuiderFollow::markerCallback, this);
  sub1_ = nh_.subscribe("/base_scan_raw", 10, &GuiderFollow::laserCallBack, this);
  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  threshold_distance_ = 1.0;
  ROS_INFO_STREAM("init");

}

GuiderFollow::~GuiderFollow()
{
}

void GuiderFollow::laserCallBack(const sensor_msgs::LaserScanConstPtr &msg)
{

  obstacle_detected_ = laserDetection_.detectObtacle(msg);
  laser_readings_ = laserDetection_.getLaserReading(msg);
  //ROS_INFO_STREAM(laser_readings_);
}

void GuiderFollow::markerCallback(const geometry_msgs::Vector3StampedPtr &msg)
{
  geometry_msgs::Vector3Stamped pose;
  pose.vector.x = msg->vector.z;
  pose.vector.y = msg->vector.x;
  pose.vector.z = msg->vector.y;

  pose_x_ = pose.vector.x;
  pose_y_ = pose.vector.y;
  pose_z_ = pose.vector.z;
  shortest_dist_ = sqrt(pow(pose.vector.x, 2) + pow(pose.vector.y, 2));
}

void GuiderFollow::navigation()
{
  while (ros::ok())
  {

    if (obstacle_detected_ == true)
    {
      if (shortest_dist_ > threshold_distance_)
      {
        twistMsg_.linear.x = 0.3;
      }
      else
      {
        twistMsg_.linear.x = -0.3;
      }

      if (pose_y_ > 0)
      {
        twistMsg_.angular.z = -0.3;
      }
      else if (pose_y_ < 0)
      {
        twistMsg_.angular.z = 0.3;
      }
      else
      {
        twistMsg_.angular.z = 0;
      }
      vel_pub_.publish(twistMsg_);
    }
    else if (obstacle_detected_ == false)
    {
      twistMsg_.angular.z = 0.3;
      twistMsg_.linear.x = 0;
      vel_pub_.publish(twistMsg_);
    }
    else if (pose_x_ == 0 || pose_y_ == 0 || pose_z_ == 0)
    {
      twistMsg_.angular.z = 0.0;
      twistMsg_.linear.x = 0;
      vel_pub_.publish(twistMsg_);
    }

    // vel_pub_.publish(twistMsg_);
  }
}

/**
 * 
 * this was modified all in the main file
// int main(int argc, char **argv)
// {
//   ros::init(argc, argv, "guider_follow");

//   ros::NodeHandle nh;

//   std::shared_ptr<GuiderFollow> robot(new GuiderFollow(nh));
//   //   std::thread vel(&GuiderFollow::velocityPublisher,robot);

//   ros::spin();

//   ros::shutdown();
//   //   vel.join();

//   return 0;
// }
**/