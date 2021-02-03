# Spawning Objects in Gazebo

[![|Solid](https://blog.generationrobots.com/wp-content/uploads/2016/03/Logo-ROS-Robot-Operating-System1-687x241.jpg)](http://wiki.ros.org/roslaunch)

## Populating the world with `roslaunch`

Inside the `BFMC_Simulator/bfmc_workspace/src/sim_pkg/launch/sublaunchers` directory, there is a launch file for each element on the map or groups of elements (you can spawn them separately while the simulator is running,  based on what you want to test). The launchers are organisez on their cattegory:

- empty map (the ground plane)
- cars
- all parking signs
- all pedestrian obstacles
- etc.

In order to use the launch files, you need to open a terminal, navigate to the `bfmc_workspace` directory and run

```sh
$ source devel/setup.bash
```

If you have no problem with computational power, you can spawn the whole environment at once (It may take some time to boot).

```sh
$ roslaunch sim_pkg map_with_all_objects_and_separators.launch
```

If you want your simmulation to run faster and adapt it to your needs, you can run the "map with terrain" or  the "map with terain and separators"

```sh
$ roslaunch sim_pkg empty_map.launch
$ roslaunch sim_pkg empty_map_with_separators.launch
```
And after the gazebo simulation started, in another terminal, you can spawn (source + roslaunch) the objects you want to interract whithin the same simulation session (stop signs, parking signs, etc.). You can delete, add and change location of the elements whithin the same session, whithout restarting the simulation. All the sublaunches but the traffic_light.launch will end the script after their spawnation.

Pay attention: 
- The traffic_lights.launch may take longer to load and it will give you the "crash like feeling". Just wait for the processes to finish.
- The obstacles_car.launch will make your simulation run considerably slower.

You can also configure your launching environment, you can create a launch file that launches multiple launch files. See the `map_with_all_objects.launch` file inside the `BFMC_Simulator/bfmc_workspace/src/sim_pkg/launch` directory. It is used to generate a fully functional map containing all competition elements. You can also add/change/remove elements on the map whithin their corresponding sublaunch.

