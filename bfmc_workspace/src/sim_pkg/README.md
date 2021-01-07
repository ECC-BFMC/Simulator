# Spawning Objects in Gazebo

[![|Solid](https://blog.generationrobots.com/wp-content/uploads/2016/03/Logo-ROS-Robot-Operating-System1-687x241.jpg)](http://wiki.ros.org/roslaunch)

## Populating the world with `roslaunch`

Inside the `BFMC_Simulator/bfmc_workspace/src/sim_pkg/launch/sublaunchers` directory, there is a launch file for each element on the map or groups of elements (you can spawn them separately while the simulator is running,  based on what you want to test):

- empty map (the ground plane)
- cars
- all parking signs
- all pedestrian obstacles
- etc.

In order to use the launch files, you need to open a terminal, navigate to the `bfmc_workspace` directory and run

```sh
$ source devel/setup.bash
```

Next, run the command for spawning the terrain:

```sh
$ roslaunch sim_pkg empty_map.launch
```

Similar to the previous command, simply replace `empty_map.launch` with the name of the launch file you want to run (as in, the objects you want to spawn).

You can also create a launch file that launches multiple launch files. See the `map_with_all_objects.launch` file inside the `BFMC_Simulator/bfmc_workspace/src/sim_pkg/launch` directory. It is used to generate a fully functional map containing all competition elements.

```sh
$ roslaunch sim_pkg map_with_all_objects.launch
```