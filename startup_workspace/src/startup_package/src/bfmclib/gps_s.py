#!/usr/bin/env python
# license removed for brevity
import rospy
import cmath
from geometry_msgs.msg import Twist


class Gps:
    def __init__(self, gps_topic_name="/rcCar/GPS"):
        """

        :param gps_topic_name: listen to this topic
        """

        # Create subscriber node
        rospy.Subscriber(gps_topic_name, Twist, self.callback)

        self._ox = None
        self._oy = None

        self.wz = None
        self.pose = complex()

    def getPose(self):
        """

        :return: complex number reprezenting the position of the car
        """
        return self.pose

    def getWz(self):
        """

        :return: Oz rotation in radians
        """
        return self.wz

    def getYaw(self):
        """
        Alias for getWz() function
        :return:
        """

        return self.getWz()

    def callback(self, msg):
        """
        
        :param msg: geometry msg Twist. The rest of the unused values form Twist msg are 0
        :return:
        """
        self.wz = round(msg.angular.z, 5)
        self._ox = round(msg.linear.x, 5)
        self._oy = round(msg.linear.y, 5)

        self.pose = complex(self._ox, self._oy)
