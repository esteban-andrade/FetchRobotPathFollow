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