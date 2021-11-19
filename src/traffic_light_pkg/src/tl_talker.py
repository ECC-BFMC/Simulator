#!/usr/bin/env python3

#
#  *****************************************************************************************
#  * @file     tl_talker.py
#  * @author   RBRO/PJ-IU
#  * @version  V1.0
#  * @date     08-12-2020 drago
#  * @brief    This file contains the traffic light operation for the start, tl1,tl2 and tl3
#  *****************************************************************************************
#

import rospy

from std_msgs.msg import Byte
from itertools import cycle
from enum import IntEnum

class trafficlight():
    # TrafficLightColor
    class Color(IntEnum):
        RED     = 0
        YELLOW  = 1
        GREEN   = 2

    def mirrorLight(self, number):
        if number == 0:
            return 2
        if number == 2:
            return 0
        return number

    
    def __init__(self):
        #Constants
        #Time for traffic light to change colors in seconds
        self.TL_interval = 1

        #Initialize the node
        rospy.init_node('traffic_light_publisher_node', anonymous=True)

        self.trafficlights = []
        #Create a new publisher, specify the topic name, type of message and queue size
        tlma = rospy.Publisher('/automobile/trafficlight/master', Byte, queue_size=1)
        tlsl = rospy.Publisher('/automobile/trafficlight/slave', Byte, queue_size=1)
        tlam = rospy.Publisher('/automobile/trafficlight/antimaster', Byte, queue_size=1)
        tlst = rospy.Publisher('/automobile/trafficlight/start', Byte, queue_size=1)
        
        self.trafficlights.append(tlma)
        self.trafficlights.append(tlsl)
        self.trafficlights.append(tlam)
        self.trafficlights.append(tlst)

        self.rate = rospy.Rate(10) 

    #Function that publishes into the TL Topic the TL message (id and state)
    def sendState(self, id, state):
        Traffic_light = Byte()
        Traffic_light = state

        self.trafficlights[id].publish(Traffic_light)

    def run(self):
        # The middle intersection 
        self.pattern = [
            self.Color.RED,
            self.Color.RED,
            self.Color.RED,
            self.Color.RED,
            self.Color.RED,

            self.Color.YELLOW,
            self.Color.YELLOW,
            
            self.Color.GREEN,
            self.Color.GREEN,
            self.Color.GREEN,
            self.Color.GREEN,
            self.Color.GREEN,

            self.Color.YELLOW,
            self.Color.YELLOW
        ]        
    
        # Cycles of patterns
        self.maincycle       = cycle(self.pattern)      
        self.last_time = rospy.get_rostime().secs - self.TL_interval*2

        while not rospy.is_shutdown():
            current_time = rospy.get_rostime().secs
            if current_time - self.last_time > self.TL_interval:
                self.main_state = next(self.maincycle)
                self.last_time  = current_time

            # Send State for the two opposite traffic lights
            self.sendState(0, self.main_state)
            self.sendState(1, self.main_state)

            # Send State for traffic light with the opposite state of the previous ones
            self.sendState(2, self.mirrorLight(self.main_state))

            #Send State for the start semaphore
            self.sendState(3, self.mirrorLight(self.main_state))

            self.rate.sleep() #publish at 10hz

if __name__ == '__main__':
    try:
        nod = trafficlight()
        nod.run()
    except rospy.ROSInterruptException:
        pass
