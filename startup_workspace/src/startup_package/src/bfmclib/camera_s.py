#!/usr/bin/env python
from __future__ import print_function

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
        self.cv_image = np.zeros((640, 480))
        self.image_sub = rospy.Subscriber("/RCcar/camera1/image_raw", Image, self.callback)

    def callback(self, data):
        """

        :param data: sensor_msg array containing the image in the Gazsbo format
        :return: nothing but sets [cv_image] to the usefull image that can be use in opencv (numpy array)
        """
        self.cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")

    def getImage(self):
        """

        :return: the image as a numpy array
        """
        return self.cv_image

    def read(self):
        """
        Alias for getImage() method
        :return:
        """
        return self.getImage()
