#!/usr/bin/env python
# license removed for brevity
import rospy
from traffic_light_pkg.msg import traffic_light
from enum import IntEnum
from time import sleep


# TrafficLightColor
class TLColor(IntEnum):
    RED = 0
    YELLOW = 1
    GREEN = 2


# TrafficLightLabel
class TLLabel(IntEnum):
    TL_START = 0
    TL0 = 0

    TL_WEST = 1
    TL1 = 1

    TL_SOUTH = 3
    TL2 = 3

    TL_EAST = 2
    TL3 = 2


class TrafficLight:
    def __init__(self, tl_topic_name="traffic_light_topic"):
        """

        :param tl_topic_name: the traffic lights states are broadcasted via [tl_topic_name] topic
        """

        # Create subscriber node
        rospy.Subscriber(tl_topic_name, traffic_light, self.callback)

        # The Start traffic light
        self.TL0_state = None

        # The West traffic light
        self.TL1_state = None

        # The South traffic light
        self.TL2_state = None

        # The East traffic light
        self.TL3_state = None

    def getTL0State(self, as_string=False):
        """

        :param as_string:
        :return:
        """

        if as_string:
            return self._getStrState(self.TL0_state)

        return self.TL0_state

    def getTL1State(self, as_string=False):
        """

        :param as_string:
        :return:
        """

        if as_string:
            return self._getStrState(self.TL1_state)

        return self.TL1_state

    def getTL2State(self, as_string=False):
        """

        :param as_string:
        :return:
        """

        if as_string:
            return self._getStrState(self.TL2_state)

        return self.TL2_state

    def getTL3State(self, as_string=False):
        """

        :param as_string:
        :return:
        """

        if as_string:
            return _getStrState(self.TL3_state)

        return self.TL3_state

    def callback(self, msg):
        # TL0
        if (msg.id == TLLabel.TL_START):
            self.TL0_state = msg.state

        # TL1
        if (msg.id == TLLabel.TL_WEST):
            self.TL1_state = msg.state

        # TL2
        if (msg.id == TLLabel.TL_SOUTH):
            self.TL2_state = msg.state

        # TL3
        if msg.id == TLLabel.TL_EAST:
            self.TL3_state = msg.state

    def _getStrState(self, int_state):
        """

        :param int_state: traffic states are received as ints 0, 1 or 2
        :return: the corresponding string
        """
        if int_state == TLColor.RED:
            return "RED"
        if int_state == TLColor.YELLOW:
            return "YELLOW"
        if int_state == TLColor.GREEN:
            return "GREEN"
