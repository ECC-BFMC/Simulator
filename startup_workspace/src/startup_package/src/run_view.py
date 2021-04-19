#!/usr/bin/python

"""
These are the libraries you need to import in your project in order to
be able to communicate with the Gazebo simulator
"""
from bfmclib.camera_view import CameraHandler
import rospy
import cv2

from time import sleep

# This line should be the first line in your program
rospy.init_node('run_view_node', anonymous=True)

cam = CameraHandler()
print("Camera loaded")

print("Select \"Frame preview\" window and press Q to exit")
cv2.namedWindow("Frame preview", cv2.WND_PROP_FULLSCREEN)
cv2.setWindowProperty("Frame preview",cv2.WND_PROP_FULLSCREEN,cv2.WINDOW_FULLSCREEN)

while 1:
	cv2.imshow("Frame preview", cam.getImage())
	key = cv2.waitKey(1)
	
	if key == ord('q'):
		cv2.destroyAllWindows()
		break

print("END")

