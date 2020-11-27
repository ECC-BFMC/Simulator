#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist


class BNO055:
    def __init__(self, bno_topic_name='/rcCar/BNO055'):
        """
        Creates a subscriber on the [bno_topic_name]

        :param bno_topic_name: by default, the object listens to /rcCar/BNO055 topic
        """
        rospy.Subscriber(bno_topic_name, Twist, self.callback)
        self.oz = None
        self.wx = None
        self.wy = None
        self.wz = None

    def callback(self, msg):
        """

        :param msg: a geometry_msgs Twist message
        :return: nothing, but sets the oz, wx, wy, wz class members
        """

        self.oz = round(msg.linear.z, 5)
        self.wx = round(msg.angular.x, 5)
        self.wy = round(msg.angular.y, 5)
        self.wz = round(msg.angular.z, 5)

    def getOz(self):
        """

        :return: [double] altitude in meters
        """
        return self.oz

    def getWx(self):
        """

        :return: [double] OX axis rotation in radians
        """
        return self.wx

    def getWy(self):
        """

        :return: [double] OY axis rotation in radians
        """
        return self.wy

    def getWz(self):
        """

        :return: [double] OZ axis rotation in radians
        """
        return self.wz

    def getRoll(self):
        """
        Alias for getWx() method
        :return:
        """
        return self.getWx()

    def getPitch(self):
        """
        Alias for getWy() method
        :return:
        """
        return self.getWy()

    def getYaw(self):
        """
        Alias for getWz() method
        :return:
        """
        return self.getWz()
