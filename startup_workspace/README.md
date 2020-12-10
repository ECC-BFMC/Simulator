# Testing your algorithms in Gazebo

[![|Solid](http://wiki.ros.org/cv_bridge?action=AttachFile&do=get&target=cvbridge.png )](http://wiki.ros.org/roslaunch)

Inside `startup_workspace/src/startup_package/src` we prepared an example file called `main.py`. First, [make sure it is executable](https://stackoverflow.com/a/304896/11454967). Then, in order to execute the file, open a terminal, navigate to the `startup_workspace` directory and run the following commands:

```sh
source devel/setup.bash
rosrun startup_package main.py
```

## More about the API

Inside `startup_workspace/src/startup_package/src/bfmclib`, you will find five libraries (**_s** stands for *subscriber* and **_p** stands for *publisher*):

#### bno055_s.py

This library simulates the functionality of the BNO055 sensor available on the real car kit. In order to use it, create a `BNO055` object and use the following methods:

1. `getOz()`              
2. `getWx()` or `getRoll()`
3. `getWy()` or `getPitch()`
4. `getWz()` or `getYaw()`

#### camera_s.py

This library converts the image from the Gazebo format into an OpenCV-compatible format using `cv_bridge`. In order to use it, create a `CameraHandler` object and call one of the following methods to get the image:

- `getImage()` or `read()` 

#### gps_s.py

This library simulates the functionality of the real GPS. In order to use it, create a `Gps` object and call the following method to get your position as a dictionary ( e.g`{'timestamp': secs_since_simulator_started, 'coor': (position, rotation)}`):

- `getGpsData()`


Similar to the real GPS, the value returned by `getPose()` is a complex number.

#### trafficlight_s.py

This library gives you the state of each traffic light on the map. In order to use it, create a `TrafficLight` object and call one of the following four methods to get the corresponding traffic light state:

- `getTL0State()` for the traffic light placed at the starting point
- `getTL1State()` for the traffic light placed in the WEST
- `getTL2State()` for the traffic light placed in the SOUTH
- `getTL3State()` for the traffic light placed in the EAST

**NOTE:** The starting point is positioned *southwards* and the parking spots are positioned *northwards*. The highway is in the east.

#### controller_p.py

This library sends commands to the rcCar on the `Command` topic. In order to use it, create a `Controller` object and call:

1. `drive(double_speed, double_wheels_angle)`
2. `stop(double_wheels_angle)`

The speed is normalized in the [-5 , 5] interval. The steering angle is normalized in the [-25, 25] interval. If you feel that your real car steers differently or drives with higher/lower speed, feel free to adjust the `MAX_STEER_ANGLE`  and `MAX_SPEED` variables.

There is also a `Response` topic, which has a subscriber listening to it by default. You can check that the command you have just sent using `drive()` was acknowledged by the car (check the `callback()` method). You can either send the `drive` or `stop` commands in open loop, or send them until the `ack` message is received – both cases are functional.