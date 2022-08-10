<img src="https://github.com/ECC-BFMC/Simulator/blob/main/Picture1.png" width=30% height=30%>

# BFMC Simulator Project

The project contains the entire Gazebo simulator developed by the organizing team as well as a ROS nod network example for gathering data from the simulator and controlling the car. 

By following the guide below you can get started with the simulator and start developing your project!


## 1. Installing the tools
- Install [Ubuntu 20.04.2.0 LTS (Focal Fossa) ](https://releases.ubuntu.com/20.04/) - Desktop Image. For best performances, avoid using a virtual machine.
- Install [ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation/Ubuntu) - Desktop-Full Install.
     

## 2. Cloning the repository

Clone the repository inside the `Documents` folder (or perform a commit on the repository)


## 3. setup of the repository

- Open a terminal in `~/Documents/Simulator` directory and run the following command:

```sh
catkin_make --pkg utils
catkin_make
```

- Two folders – `devel` and `build` – will be generated inside the `repository` directory. 

- Gazebo needs to know where the workspace's packages and models are, so you will need to add them to the gazebo environment variable list. The easiest and cleanest way is to add them to the source file of the simulation, so it won't interfear with other projects:

```sh
gedit devel/setup.bash
```

and add those two lines at the begining of the file (don't forget to change {YOUR_USER} with your actual user name).

```sh
export GAZEBO_MODEL_PATH="/home/{YOUR_USER}/Documents/Simulator/src/models_pkg:$GAZEBO_MODEL_PATH"
export ROS_PACKAGE_PATH="/home/{YOUR_USER}/Documents/Simulator/src:$ROS_PACKAGE_PATH"
```

## 4. Running of the simulation

For each terminal where you plan to use the ROS, you need to source the repository itself:

```sh
source devel/setup.bash
```
- Finally, run the following command in order to start the entire simulation (the simulaiton is heavy, it may take many resources):

```sh
roslaunch sim_pkg map_with_all_objects.launch
```


## 5. Interaction with the simulation

The simulation can interact directly with the car or it can be used as a stand-alone environment on your PC.


### 5.1. Interaction with the rcCar

Both the car and the PC running the simulation have to be on the same network and the ssh communication has to be enabled on the RPi.
In order for the nodes to be able to communicate between them, some environmental variables have to be set. A script was created for this purpose:
On the RPI, you have to run the script as follows:
```sh
source src/utils/network.sh PC_IP
```
On the PC running the simulation, you have to run the script as follows:
```sh
source src/utils/network.sh
```
This setup will make the nodes on your car interact with the roscore from the PC, and you will be able to see the entire setup of the network. 
The file have to be soruced for each terminal. 
The core can be swapped to run on the phisical car as well.

Run the simulation on the PC:
```sh
roslaunch sim_pkg map_with_car.launch
```
Run the control nodes of the car on the RPI:
```sh
roslaunch utils start_car_virtual.launch
```

Now the simulator will publish some info on the topics and you can subscribe to them from your car (automobile/image_raw, automobile/localisation, automobile/IMU, automobile/feedback, automobile/semaphores/*)

Now the simulator will subscribe to some info on the topics and you can publish on them from your car (automobile/command)

### 5.2. Interaction with the PC

To check an example of publishing & subscribing, after the simulaiton was started, you can open two other terminals and source the devel/setup.bash inside.
on one terminal, execute
```sh
rosrun example camera.py
```
and on another one you can execute
```sh
rosrun example control.py
```

If the setup for interacting with the car is done, the phisical car will also interact with the two scripts, as well as the virtual one. 
We suggest, if you plan to develop on the PC, to create another workspace for the project itself. 


## 6. Camera Setup

### 6.1 Change Resolution

Inside `src/models_pkg/camera/model.sdf`, you will find the `<width>` and `<height>` tags. Modifying them will allow you to change the camera resolution. You don't need to recompile the workspace after this change.

### 6.2. Change Position

Inside `src/models_pkg/rcCar_assembly/model.sdf`, you will find the inclusion of `<uri>model://camera</uri>`. Inside that same `<include>` tag, there is also a `<pose>` tag, which you will need to modify [according to the SDF format specification](http://sdformat.org/spec?ver=1.6&elem=model#include_pose) in order to change the camera's position. You don't need to recompile the workspace after this change.

```
<!-- All constants of double data type, with angles in radians and "." (dot) as decimal separator -->
<pose> X Y Z ROLL PITCH YAW </pose> 
```

## 7. Other tips

- If you want to start the testing from scratch, instead of restarting gazebo, you can only restart the simulation with the help of the ROS services:
```sh
$ rosservice call /gazebo/reset_simulatio
```

- Deactivate GUI from the launch in order to save some computational power;

- Play with rqt tool in order to check the images and other topic messages, frequency, etc. 

- You can change the resolution of the map from `src/models_pkg/track/materials/scripts/bfmc_track.material`. The available maps are under the textures directory. 
Bigger the resolution, bigger the requirements of the simulation.

- Inside the `src/sim_pkg/launch/sublaunchers` directory, there is a launch file for each type of elements on the map or groups of elements. You can also spawn some of them separately while the simulator is running, based on the requirements at the moment. 

You can also configure your own launching files, you can create a launch file that includes multiple launch files. See the `map_with_all_objects.launch` file inside the `src/sim_pkg/launch` as an example.

In order to use the launch files, you need to source the devel/setup.bash
