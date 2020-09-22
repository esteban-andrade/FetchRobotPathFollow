#include "../include/FetchRobotPathFollow/guider_follow.h"

GuiderFollow::GuiderFollow(ros::NodeHandle nh)
    :nh_(nh)
{
    marker_sub_ = nh_.subscribe("/aruco_single/position", 1000, &GuiderFollow::markerCallback, this);

    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    threshold_distance_ = 1.0;
    ROS_INFO_STREAM("init");
}

GuiderFollow::~GuiderFollow(){

}

void GuiderFollow::markerCallback(const geometry_msgs::Vector3StampedPtr &msg){
    geometry_msgs::Vector3Stamped pose;
    pose.vector.x = msg->vector.z;
    pose.vector.y = msg->vector.x;
    pose.vector.z = msg->vector.y;

    double shortest_dist = sqrt(pow(pose.vector.x,2) + pow(pose.vector.y,2));

    if (shortest_dist > threshold_distance_){
        twistMsg_.linear.x = 0.3;
    }
    else{
        twistMsg_.linear.x = -0.3;
    }

    if (pose.vector.y > 0){
      twistMsg_.angular.z = -0.3;
    }
    else if(pose.vector.y < 0){
      twistMsg_.angular.z = 0.3;
    }
    else{
      twistMsg_.angular.z = 0;
    }

    vel_pub_.publish(twistMsg_);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "guider_follow");

  ros::NodeHandle nh;
  
  std::shared_ptr<GuiderFollow> robot(new GuiderFollow(nh));
//   std::thread vel(&GuiderFollow::velocityPublisher,robot);

  ros::spin();

  ros::shutdown();
//   vel.join();

  return 0;
}
    