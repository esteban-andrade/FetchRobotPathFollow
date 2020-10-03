# FetchRobotPathFollow
Here is the Repository for Fetch robot following a Path based on QR codes.

>Note Please Have the turtle bot and Fetch package installed in the catkin workspace. This package will build on top of that.


## Aruco Marker Detection
Install Depenedancy

```bash
cd ~/catkin_ws/src
git clone https://github.com/pal-robotics/aruco_ros.git
cd ~/catkin_ws
catkin_make
```

## Operation
Launch the world, fetch & guider robot, joy_controller_teleop (requries bluetooth controller) nodes:
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
```bash
cd ~/catkin_ws/src
rosrun rviz rviz -d fetch_robot_path_follow/rviz/rviz_fetch.rviz
```