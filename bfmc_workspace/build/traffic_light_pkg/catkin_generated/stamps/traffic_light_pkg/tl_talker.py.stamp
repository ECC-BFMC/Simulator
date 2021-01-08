#!/usr/bin/env python

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

from traffic_light_pkg.msg import traffic_light
from itertools import cycle
from enum import IntEnum

# Mirror the traffic lights in a "+" intersection
def mirrorLight(number):
    """
    For the intersection, two traffic lights will have the same lights on,
    whereas the other two will have the opposite lights on
    """

    if number == 0:
        return 2
    
    if number == 2:
        return 0

    return number

# TrafficLightColor
class Color(IntEnum):
    RED     = 0
    YELLOW  = 1
    GREEN   = 2

#Constants
#Time for traffic light to change colors in seconds
TL_interval = 1


#Create a new publisher, specify the topic name, type of message and queue size
pub = rospy.Publisher('traffic_light_topic', traffic_light, queue_size=2)

#Initialize the node
rospy.init_node('traffic_light_publisher_node', anonymous=True)

#Initialization
Traffic_light = traffic_light()

#Function that publishes into the TL Topic the TL message (id and state)
def sendState(id,state):
    
    traffic_light.id    = id
    traffic_light.state = state

    pub.publish(Traffic_light)


def talker():
    
    # Set loop rate for publication
    # 10z, every 0.1s as stated in bfmc docs
    rate = rospy.Rate(10) 

    """
    For each entry in the patterns array, the traffic light cycle will last 1 second longer

    - if Color.RED    (or 0) is added, the red     traffic light color will last 1 second longer
    - if Color.YELLOW (or 1) is added, the yellow  traffic light color will last 1 second longer
    - if Color.GREEN  (or 2) is added, the green   traffic light color will last 1 second longer
    
    The length of the pattern list equals the traffic light cycle duration (in seconds)
    """

    # The middle intersection 
    pattern_main = [
        Color.RED,
        Color.RED,
        Color.RED,
        Color.RED,
        Color.RED,

        Color.YELLOW,
        Color.YELLOW,
        
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,

        Color.YELLOW,
        Color.YELLOW
    ]

    pattern_start = [
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,
        Color.GREEN,

        Color.YELLOW,
        Color.YELLOW,

        Color.RED,
        Color.RED,
        Color.RED,
        Color.RED,
        Color.RED,
        
        Color.YELLOW,
        Color.YELLOW
    ]
    
   
    # Cycles of patterns
    maincycle       = cycle(pattern_main)
    startcycle      = cycle(pattern_start)
    
    #Initializations
    main_state      = next(maincycle)
    start_state     = next(startcycle)
    last_time       = rospy.get_rostime().secs

    while not rospy.is_shutdown():

        # Get time from ros
        current_time = rospy.get_rostime().secs

        # Change pattern element if the TL_interval(s) has passed 
        if ((current_time - last_time) > TL_interval):
            main_state  = next(maincycle)
            start_state = next(startcycle)
            last_time   = current_time

        # Send State for the two opposite traffic lights
        sendState(1, main_state)
        sendState(2, main_state)

        # Send State for traffic light with the opposite state of the previous ones
        sendState(3, mirrorLight(main_state))

        #Send State for the start semaphore
        sendState(0, start_state)

        rate.sleep() #publish at 10hz

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
