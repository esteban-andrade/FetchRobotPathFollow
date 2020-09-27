# FetchRobotPathFollow
Here is the Repository for Fetch robot following a Path based on QR codes.

>Note Please Have the turtle bot and Fetch package installed in the catkin workspace. The nodes will build on top of that.

>Note: If the models do not spawn. Please run the following. 
 ```bash
 cp -avr ~/catkin_ws/src/fetch_robot_path_follow/models/ ~/.gazebo/
 ```

## Aruco Marker Detection
Install Depenedancy

```bash
cd ~/catkin_ws/src
git clone https://github.com/pal-robotics/aruco_ros.git
cd ~/catkin_ws
catkin_make
```

## Operation
Launch world, robots, joy_controller_teleop:
```bash
roslaunch fetch_robot_path_follow mazeFetch.launch
```
 Marker tracking and guider following:
```bash
 roslaunch fetch_robot_path_follow follow_guider.launch
```


## VISP Tracker
Note: This is another Visual servoing package to track a QR code. This will aid with external visualization of the Marker. 
This will be optional.


~~~~
```Dependencies for Visual Servoing package
sudo apt-get install libvisp-dev libvisp-doc visp-images-data
sudo apt-get install ros-<distro>-visp
sudo apt-get install ros-<distro>-vision-visp
```
~~~~

```In your catkin workspace add this repo. The Custom package will build on top.
cd ~/catkin_ws/src
git clone https://github.com/lagadic/vision_visp.git
cd ~/catkin_ws
catkin_make
```

~~~~
To run it please type: 

````
roslaunch fetch_robot_path_follow qr_pbvs.launch
````
