# FetchRobotPathFollow
Here is the Repository for Fetch robot following a Path based on QR codes.
## Authors & Contributions
* Esteban Andrade
    * Environment/World creation
    * Obstacle detection 
    * Repository Setup
    * Documentation
* Ajal Singh
    * Controller teleop node (Guider control)
    * Guider Following
    * Demo video
    * Documentation

## Dependancies
Please have the Turtlebot and Fetch packages installed in your catkin workspace. This package will build on top of these dependencies.
## Aruco Marker Detection
Aruco marker detection is used to detect the guider robot.
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
 cp -avr ~/catkin_ws/src/fetch_robot_path_follow/models/ ~/.gazebo/models
 ```

>Note: If you do not have a bluetooth controller available, standard keyboard teleop can be used:
```bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.py /cmd_vel:=/robot1/cmd_vel
```

 Launch Marker tracking and guider following:
```bash
 roslaunch fetch_robot_path_follow follow_guider.launch
```
The guider can be made traverse through the world using the 2 joysticks on your controller or keyboard using teleop_twist.

## Expected Behaviour
The fetch robot will follow the Guider robot as it traverses through the environment as long as the AR marker is clearly seen by the Fetch's RGBD camera.
If the Guider cannot be seen, the Fetch will sweep clockwise and anti-clockwise until the Guider is located. If the Guider is not found, the Fetch will stop and wait for the Guider to traverse to a location within camera view before resuming the following operation. 
If an obstacle obstructs the path of the Fetch while the Guider is in view, the Fetch will cease following and wait for the Guider to relocate.
If an obstacle is detected when the Guider is not in view (i.e has just left the camera frame) the Fetch will back up and scan the area in search of the guider.
The Fetch can view and read other AR markers within the environment, however they will not affect its following operation.

## RVIZ Visualisation
To view sensor and message data:
```bash
cd ~/catkin_ws/src
rosrun rviz rviz -d fetch_robot_path_follow/rviz/rviz_fetch.rviz
```

## Demonstration Video
[![Demostration video](https://img.youtube.com/vi/TRuqb9f4Vtk/sddefault.jpg)](https://youtu.be/TRuqb9f4Vtk)

