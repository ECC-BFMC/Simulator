#!/usr/bin/env python2

#
#  ***************************************************************************************
#  * @file     tl_listener.py
#  * @author   RBRO/PJ-IU
#  * @version  V1.0
#  * @date     21-08-2020 MMESTRE
#  * @brief    This file contains the listener for the state of the track's traffic lights
#  ***************************************************************************************
#

import rospy
from traffic_light_pkg.msg import traffic_light

#State Initialization
TF1_state = 0
TF2_state = 0
TF3_state = 0
TFstart_state = 0

#Print function for visualization of TF States
def printState(start, tf1, tf2, tf3):
    print("Start TF: " + str(start) + "\n\tFirst TF: " + str(tf1) + "\n\tSecond TF: " + str(tf2) + "\n\t\tThird TF: " + str(tf3))
    

#Callback function that associates the state of each TF to their respective variables
def traffic_light_callback(traffic_light_message):
    global TF1_state, TF2_state, TF3_state, TFstart_state

    #State in Words
    TEXT = True

    #Change state into words for easier comprehension
    if TEXT:
        if traffic_light_message.state == 0:
            traffic_light_message.state = "RED"
        if traffic_light_message.state == 1:
            traffic_light_message.state ="YELLOW"
        if traffic_light_message.state == 2:
            traffic_light_message.state = "GREEN"

    #Register state of Start Traffic Light
    if (traffic_light_message.id == 0):
        TFstart_state = traffic_light_message.state

    #Register state of First Traffic Light
    if (traffic_light_message.id == 1):
        TF1_state = traffic_light_message.state

    #Register state of Second Traffic Light
    if (traffic_light_message.id == 2):
        TF2_state = traffic_light_message.state

    #Register state of Third Traffic Light
    if (traffic_light_message.id == 3):
        TF3_state = traffic_light_message.state
        
    #Call for Printing function
    printState(TFstart_state,TF1_state,TF2_state,TF3_state)

def listener():
    rospy.init_node('traffic_light_subscriber_node', anonymous=True)
    #Subscribes traffic_light_topic, uses traffic_light.msg type of message, and calls the traffic_light_callback function
    rospy.Subscriber("traffic_light_topic", traffic_light, traffic_light_callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
