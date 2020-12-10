#!/usr/bin/env python
# license removed for brevity
import rospy
from car_plugin.msg import Command
from car_plugin.msg import Response

from time import sleep

class Controller:
    def __init__(self, command_topic_name="/rcCar/Command", response_topic_name="/rcCar/Response"):
        """

        :param command_topic_name: drive and stop commands are sent on this topic
        :param response_topic_name: "ack" message is received on this topic
        """
        self.pub = rospy.Publisher(command_topic_name, Command, queue_size=2)

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
        speed = Controller.normalizeSpeed(speed)
        angle = Controller.normalizeSteer(angle)

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
        angle = Controller.normalizeSteer(angle)

        # Set message
        self.msg_command.msg_val = [angle]

        # Publish
        self.pub.publish(self.msg_command)

    # TODO: Not used yet. Can be implemented
    def callback(self, data):
        if data.response == "ack":
            self.received = True

    @staticmethod
    def normalizeSpeed(val):
        """
        :return: normalized value
        """

        if val < -1:
            val = -1
        
        elif val > 1:
            val = 1

        return val

    @staticmethod
    def normalizeSteer(val):
        """
        :return: normalized value
        """
        if val < -25:
            val = -25

        elif val > 25:
            val = 25

        return Controller.map_f(val, -25, 25, -35, 35)

    @staticmethod
    def map_f(x, a, b, c, d):
        return (x - a) * (d - c) / (b - a) + c
