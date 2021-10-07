#!/usr/bin/env python3

# Copyright (c) 2019, Bosch Engineering Center Cluj and BFMC organizers
# All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.

# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.

# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE

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
