# FetchRobotPathFollow
Here is the Repository for Fetch robot following a Path based on QR codes.

Note Please Have the tuttle bots and Fetch package installed in the catkin workspace. The nodes will build on top of that.

Note: If all the models do not launch. Please do the following. 
 Open /home/.gazebo   
 and place all the files that are within the models folder in that directory. 

For QR code detection install the following: (you may need to install pip)

```bash
sudo apt-get install libzbar0
pip install pyzbar
pip install pyzbar[scripts]

```



Dependencies for Visual Servoing package
sudo apt-get install libvisp-dev libvisp-doc visp-images-data
sudo apt-get install ros-<distro>-visp
sudo apt-get install ros-melodic-vision-visp

In your catkin workspace add this repo. The Custom package will build on top.
cd catkin_ws/src
git clone https://github.com/lagadic/vision_visp.git
cd ..
catkin_make
 
