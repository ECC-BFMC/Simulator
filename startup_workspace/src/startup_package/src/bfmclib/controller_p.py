#!/usr/bin/env python
# license removed for brevity
import rospy
from car_plugin.msg import Command
from car_plugin.msg import Response

from time import sleep

MAX_STEER_ANGLE = 25
MAX_SPEED = 5


class Controller:
    def __init__(self, command_topic_name="/rcCar/Command", response_topic_name="/rcCar/Response"):
        """

        :param command_topic_name: drive and stop commands are sent on this topic
        :param response_topic_name: "ack" message is received on this topic
        """
        self.pub = rospy.Publisher(command_topic_name, Command, queue_size=10)

        # Wait for publisher to register to roscore -
        # TODO: This is a temporary fix. Problem with timing
        sleep(1)

        # Subscriber node
        rospy.Subscriber(response_topic_name, Response, self.callback)

        # Set a flag: publish until ack received...
        # TODO: Not used yet but can be implemented
        self.received = False

        # Create an empty custom Command message
        self.msg_command = Command()

    def drive(self, speed=0.0, angle=0.0):
        """

        :param speed:
        :param angle:
        :return: nothing but publish to [command_topic_name]
        """

        # MOVE
        self.msg_command.key.v = 1

        # Normalize both speed and angle
        speed = Controller.normalize(speed, -1 * abs(MAX_SPEED), abs(MAX_SPEED))
        angle = Controller.normalize(angle, -1 * abs(MAX_STEER_ANGLE), abs(MAX_STEER_ANGLE))

        self.msg_command.msg_val = [speed, angle]

        # The message will be sent until "ack" is received
        self.pub.publish(self.msg_command)

    def stop(self, angle=0.0):
        """
        This simulates the braking behaviour from the Nucleo
        :param angle:
        :return:
        """

        # BRAKE
        self.msg_command.key.v = 2

        # Normalize angle
        angle = Controller.normalize(angle, -1 * abs(MAX_STEER_ANGLE), abs(MAX_STEER_ANGLE))

        # Set message
        self.msg_command.msg_val = [angle]

        # Publish
        self.pub.publish(self.msg_command)

    # TODO: Not used yet. Can be implemented
    def callback(self, data):
        if data.response == "ack":
            self.received = True

    @staticmethod
    def normalize(val, min, max):
        """

        :param val: the value you don't want to exceed [min, max]
        :param min:
        :param max:
        :return: normalized value
        """
        if max < min:
            tmp = max
            max = min
            min = tmp

        if val < min:
            val = min
        elif val > max:
            val = max

        return val
