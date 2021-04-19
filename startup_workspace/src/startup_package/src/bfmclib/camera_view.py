#!/usr/bin/env python

import roslib
import sys
import rospy
import cv2
import numpy as np
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


class CameraHandler():
    def __init__(self):
        """
        Creates a bridge for converting the image from Gazebo image intro OpenCv image
        """
        self.bridge = CvBridge()
        self.cv_imageF = np.zeros((1080, 1920))
        self.cv_imageB = np.zeros((480, 640))
        self.image_follow = rospy.Subscriber("/rcCar/rcCar/camera_follow/image_raw", Image, self.callbackF)
        self.image_birdeye = rospy.Subscriber("/rcCar/rcCar/camera_birdeye/image_raw", Image, self.callbackB)\

    def callbackF(self, data):
        """

        :param data: sensor_msg array containing the image in the Gazsbo format
        :return: nothing but sets [cv_image] to the usefull image that can be use in opencv (numpy array)
        """
        self.cv_imageF = self.bridge.imgmsg_to_cv2(data, "bgr8")

    def callbackB(self, data):
        """

        :param data: sensor_msg array containing the image in the Gazsbo format
        :return: nothing but sets [cv_image] to the usefull image that can be use in opencv (numpy array)
        """
        self.cv_imageB = self.bridge.imgmsg_to_cv2(data, "bgr8")

    def getImage(self):
        """

        :return: the image as a numpy array
        """
        cv_image = self.cv_imageF
	try:
        	cv_image[600:1080,0:640] = self.cv_imageB
	except: pass
        return cv_image
