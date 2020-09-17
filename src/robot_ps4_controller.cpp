#include "../include/FetchRobotPathFollow/robot_ps4_controller.h"

RobotTeleopJoy::RobotTeleopJoy(ros::NodeHandle nh)
    :nh_(nh)
{
    joy_sub_ = nh_.subscribe("/joy", 1000, &RobotTeleopJoy::joyCallback, this);

    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    
}

RobotTeleopJoy::~RobotTeleopJoy(){

}

void RobotTeleopJoy::joyCallback(const sensor_msgs::JoyPtr &msg){
    
    twistMsg_.linear.x = msg->axes.at(1)*2;
    twistMsg_.angular.z = msg->axes.at(0)*2;
}

void RobotTeleopJoy::velocityPublisher(){
    ros::Rate loop_rate(20);
    while (ros::ok()){
        vel_pub_.publish(twistMsg_);
        loop_rate.sleep();
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_ps4_controller");

  ros::NodeHandle nh;
  
  std::shared_ptr<RobotTeleopJoy> robot(new RobotTeleopJoy(nh));
  std::thread vel(&RobotTeleopJoy::velocityPublisher,robot);

  ros::spin();

  ros::shutdown();
  vel.join();

  return 0;
}
