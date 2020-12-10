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

        self._ox  = None
        self._oy  = None
        self._wz  = None

        self._rot        = complex()
        self._pose       = complex()

        self.gps_data     = {'timestamp': None, 'coor': None}

    def getGpsData(self):
        """
        This is the method that provides the data similar to the real gps from the BFMC
        """
        return self.gps_data

    def callback(self, msg):
        """
        
        :param msg: geometry msg Twist. The rest of the unused values form Twist msg are 0
        :return:
        """
        self._wz = round(msg.angular.z, 5)
        self._ox = round(msg.linear.x, 5)
        self._oy = round(msg.linear.y, 5)

        self._pose = complex(self._ox, self._oy)
        self._rot = complex(cmath.cos(self._wz), cmath.sin(self._wz))

        self.gps_data = {'timestamp': (rospy.get_rostime().secs *1e9 + rospy.get_rostime().nsecs)/1e9 , 'coor': (self._pose, self._rot)}

