#!/usr/bin/env python
from __future__ import print_function
import rospy
# from beginner_tutorials.msg import QR
from pyzbar.pyzbar import decode
import numpy as np
import cv2
import time
import random
from geometry_msgs.msg import PoseWithCovarianceStamped
from tf.transformations import euler_from_quaternion
from visualization_msgs.msg import Marker
from std_msgs.msg import Header, ColorRGBA
from geometry_msgs.msg import Quaternion, Pose, Point, Vector3

msg = QR()
scanned_codes = []
def talker():
    
    
    #msg.x = decodedObject.rect.left
    #msg.y = decodedObject.rect.top
    #msg.Type = decodedObject.type
    msg.Data = coord

    #rospy.loginfo(msg)
    pub.publish(msg)      
	        
    #except rospy.ROSInterruptException: pass
    

def testDevice(source):
   cap = cv2.VideoCapture(source) 
   if cap is None or not cap.isOpened():
       print('Warning: unable to open video source: ', source)
       


if __name__ == "__main__":
    
    rospy.init_node('QR_NODE')
    pub = rospy.Publisher('QR_chatter', QR, queue_size = 10)
    r = rospy.Rate(10) #10hz
    
    print("ping")
    
    # get the webcam:
    testDevice(2)

    cap = cv2.VideoCapture('rtsp://slam:slamslam@192.168.1.2:8080/h264_pcm.sdp')

    cap.set(3, 640)
    cap.set(4, 480)
    # 160.0 x 120.0
    # 176.0 x 144.0
    # 320.0 x 240.0
    # 640.0 x 480.0
    # 1024.0 x 768.0
    # 1280.0 x 1024.0
    time.sleep(2)

    font = cv2.FONT_HERSHEY_SIMPLEX
    
    try:
        while (cap.isOpened()):
            
            # Capture frame-by-frame
            ret, frame = cap.read()
            # Our operations on the frame come here
            grayFrame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)            
            
            decodedObjects = decode(grayFrame)

            for decodedObject in decodedObjects:
                if decodedObject.data not in scanned_codes:
                    del scanned_codes[:]
                    coord = decodedObject.data
                    scanned_codes.append(coord)
                    print(scanned_codes)
                    talker()
                    break
                    
                points = decodedObject.polygon

                # If the points do not form a quad, find convex hull
                if len(points) > 4:
                    hull = cv2.convexHull(np.array([point for point in points], dtype=np.float32))
                    hull = list(map(tuple, np.squeeze(hull)))
                else:
                    hull = points;
                
                      
    except Exception as e:
        print(e)
    finally:
        # When everything done, release the capture
        cap.release()
        cv2.destroyAllWindows()