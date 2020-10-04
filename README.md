# FetchRobotPathFollow
## Authors & Contributions
* Esteban Andrade
    * Environment/World creation
    * Obstacle detection 
* Ajal Singh
    * Controller teleop node (Guider control)
    * Guider Following
    * Demo video

## Dependancies
Here is the Repository for Fetch robot following a Path based on QR codes.

> Please have the Turtlebot and Fetch packages installed in your catkin workspace. This package will build on top of these dependencies.
## Aruco Marker Detection
Aruco marker detection is used to detect the guider the robot.
Install:

```bash
cd ~/catkin_ws/src
git clone https://github.com/pal-robotics/aruco_ros.git
cd ~/catkin_ws
catkin_make
```

## Installation
To install this package, run the following commands:
```bash
cd ~/catkin_ws/src
git clone https://github.com/esteban-andrade/FetchRobotPathFollow.git
cd ~/catkin_ws
catkin_make
```

## Operation
Launch the world, fetch & guider robots, and controller teleop node (requries bluetooth controller):
```bash
roslaunch fetch_robot_path_follow mazeFetch.launch
```
>Note: If the models do not spawn. Please run the following and relaunch. 
 ```bash
 cp -avr ~/catkin_ws/src/fetch_robot_path_follow/models/ ~/.gazebo/
 ```

>Note: If you do not have a bluetooth controller available, standard keyboard teleop can be used:
```bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py /cmd_vel:=/robot1/cmd_vel
```

 Launch Marker tracking and guider following:
```bash
 roslaunch fetch_robot_path_follow follow_guider.launch
```

## RVIZ Visualisation
To view sensor and message data:
```bash
cd ~/catkin_ws/src
rosrun rviz rviz -d fetch_robot_path_follow/rviz/rviz_fetch.rviz
```

## Demonstration Video
[![Demostration video](https://img.youtube.com/vi/TRuqb9f4Vtk/sddefault.jpg)](https://youtu.be/TRuqb9f4Vtk)

