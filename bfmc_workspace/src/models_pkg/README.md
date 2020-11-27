# Camera Setup

[![|Solid]( https://cdn.shopify.com/s/files/1/2187/3161/products/aa784c9b38749245b6a4651ea5aaefda_128x.png?v=1571708699 )](http://gazebosim.org/tutorials?tut=ros_gzplugins)


## Change Resolution

Inside `bfmc_workspace/src/models_pkg/camera/model.sdf`, you will find the `<width>` and `<height>` tags. Modifying them will allow you to change the camera resolution. You don't need to recompile the workspace after this change.

See also `startup_workspace`, where we provided some useful libraries for running your Python code in the Gazebo simulator.

## Change Position

Also inside `bfmc_workspace/src/models_pkg/rcCar_assembly/model.sdf`, you will find the inclusion of `<uri>model://camera</uri>`. Inside that same `<include>` tag, there is also a `<pose>` tag, which you will need to modify [according to the SDFormat specification](http://sdformat.org/spec?ver=1.6&elem=model#include_pose) in order to change the camera's position. You don't need to recompile the workspace after this change.

```
<!-- All constants of double data type, with angles in radians and "." (dot) as decimal separator -->
<pose> X Y Z ROLL PITCH YAW </pose> 
```