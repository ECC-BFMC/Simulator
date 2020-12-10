#!/usr/bin/python

"""
These are the libraries you need to import in your project in order to
be able to communicate with the Gazebo simulator
"""
from bfmclib.gps_s import Gps
from bfmclib.bno055_s import BNO055
from bfmclib.camera_s import CameraHandler
from bfmclib.controller_p import Controller
from bfmclib.trafficlight_s import TLColor, TLLabel, TrafficLight

import rospy
import cv2

from time import sleep

# This line should be the first line in your program
rospy.init_node('main_node', anonymous=True)

cam = CameraHandler()
print("Camera loaded")

car = Controller()
print("Controller loaded")

sem = TrafficLight()
print("Traffic lights listener")

gps = Gps()
print("Gps loaded")

bno = BNO055()
print("BNO055 loaded")

print("Sending move with speed 0.2, steering -25")
car.drive(0.2, -25)
sleep(5)

print("Sending move with speed 0.2, steering 25")
car.drive(0.2, 25)
sleep(5)

print("Select \"Frame preview\" window and press Q to exit")

steering = 0.0
speed = 0.0

while 1:
	cv2.imshow("Frame preview", cam.getImage())
	
	key = cv2.waitKey(1)
	
	if key == ord('q'):
		cv2.destroyAllWindows()
		break

print("Car stopped. \n END")
car.stop(0.0)
