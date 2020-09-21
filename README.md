# FetchRobotPathFollow
Here is the Repository for Fetch robot following a Path based on QR codes.

>Note Please Have the turtle bot and Fetch package installed in the catkin workspace. The nodes will build on top of that.

>Note: If the models do not spawn. Please run the following. 
 ```bash
 cp -avr ~/catkin_ws/src/fetch_robot_path_follow/models/ ~/.gazebo/
 ```

~~For QR code detection install the following: (you may need to install pip)~~

```bash
sudo apt-get install libzbar0
pip install pyzbar
pip install pyzbar[scripts]

```



~~Dependencies for Visual Servoing package~~
```
sudo apt-get install libvisp-dev libvisp-doc visp-images-data
sudo apt-get install ros-<distro>-visp
sudo apt-get install ros-<distro>-vision-visp
```
~~In your catkin workspace add this repo. The Custom package will build on top.~~

```
cd ~/catkin_ws/src
git clone https://github.com/lagadic/vision_visp.git
cd ~/catkin_ws
catkin_make
```

## Aruco Marker Detection
Install Depenedancy

```bash
cd ~/catkin_ws/src
git clone https://github.com/pal-robotics/aruco_ros.git
cd ~/catkin_ws
catkin_make
```

Under the **ARUCO_ROS** package, replace **_single.launch_** file with the following:
```xml
<launch>

    <arg name="markerId"        default="369"/>
    <arg name="markerSize"      default="0.36"/>    <!-- in m -->
    <arg name="eye"             default="/head_camera/rgb/"/>
    <arg name="marker_frame"    default="aruco_marker_frame"/>
    <arg name="ref_frame"       default="result"/>  <!-- leave empty and the pose will be published wrt param parent_name -->
    <arg name="corner_refinement" default="LINES" /> <!-- NONE, HARRIS, LINES, SUBPIX -->


    <node pkg="aruco_ros" type="single" name="aruco_single">
        <remap from="/camera_info" to="$(arg eye)/camera_info" />
        <remap from="/image" to="$(arg eye)/image_raw" />
        <param name="image_is_rectified" value="True"/>
        <param name="marker_size"        value="$(arg markerSize)"/>
        <param name="marker_id"          value="$(arg markerId)"/>
        <param name="reference_frame"    value="$(arg ref_frame)"/>   <!-- frame in which the marker pose will be refered -->
        <param name="camera_frame"       value="$(arg eye)_camera_optical_frame"/>
        <param name="marker_frame"       value="$(arg marker_frame)" />
        <param name="corner_refinement"  value="$(arg corner_refinement)" />
    </node>

</launch>
 ```

 Run:
```bash
 roslaunch aruco_ros single.launch
```