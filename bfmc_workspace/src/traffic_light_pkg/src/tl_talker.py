#!/usr/bin/env python

#
#  *****************************************************************************************
#  * @file     tl_talker.py
#  * @author   RBRO/PJ-IU
#  * @version  V1.0
#  * @date     21-08-2020 MMESTRE
#  * @brief    This file contains the traffic light operation for the start, tl1,tl2 and tl3
#  *****************************************************************************************
#

import rospy
from traffic_light_pkg.msg import traffic_light
from itertools import cycle
import time

#Create a new publisher, specify the topic name, type of message and queue size
pub = rospy.Publisher('traffic_light_topic', traffic_light, queue_size=10)
#Initialize the node
rospy.init_node('traffic_light_publisher_node', anonymous=True)
#Initialization
Traffic_light = traffic_light()

#Function that publishes into the TL Topic the TL message (id and state)
def sendState(id,state):
    traffic_light.id = id
    traffic_light.state = state
    pub.publish(Traffic_light)


def talker():
    #Set loop rate for publication
    rate = rospy.Rate(10) # 10z, every 0.1s as stated in bfmc docs
    #Time for traffic light to change colors (1s)
    TL_interval = 1

    #Numbers of the pattern repeat to simulate a longer duration, add a number means adding 1s of duration to the cycle
    #: Patterns to be sent, main -> main traffic light, start -> traffic light in the start
    pattern_main = [0,0,0,0,0,0,0,2,2,2,2,2,1,1]
    pattern_start = [2,2,2,2,2,1,1,0,0,0,0,0,0,0]
    #Mirror pattern that acts reverse to the main pattern of TL 1 and 2
    pattern_mirrormain = [2,2,2,2,2,1,1,0,0,0,0,0,0,0]

    #: Cycles of patterns
    maincycle = cycle(pattern_main)
    mirrormaincycle = cycle(pattern_mirrormain)
    startcycle = cycle(pattern_start)

    #Initializations
    main_state = next(maincycle)
    start_state = next(mirrormaincycle)
    mirrormain_state = next(startcycle)

    old_time = time.time()

    while not rospy.is_shutdown():

        #: Change pattern element each second
        if ((time.time()-old_time)>TL_interval):
            main_state = next(maincycle)
            start_state = next(mirrormaincycle)
            mirrormain_state = next(startcycle)
            old_time = time.time()

        #Send State for traffic light 1 and 2 with synched states
        sendState(1,main_state)
        sendState(2,main_state)
        #Send State for traffic light 3 with the opposite state of 1 and 2
        sendState(3,mirrormain_state)
        #Send State for the start semaphore
        sendState(0,start_state)


        rate.sleep() #publish at 10hz

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
