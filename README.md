# Installation
Install turtlebot_simulator package
```
   $ sudo apt-get install ros-indigo-turtlebot-simulator
   $ sudo apt-get install ros-indigo-turtlebot-apps ros-indigo-turtlebot-rviz-launchers
   $ sudo apt-get install ros-indigo-ros-controllers ros-indigo-gazebo-ros-control ros-indigo-controller-manager
```
Copy Pengo project from the GitHub
```
   $ cd
   $ mkdir -p workspace/src
   $ cd workspace/src
   $ git clone https://github.com/cogniteam/pengo.git
```
Compile Pengo project
```
   $ cd ~/workspace
   $ catkin_make
```


# Running
In first terminal window (to run environment)
```
   $ source ~/workspace/devel/setup.bash
   $ roslaunch pengo pengo_world.launch
```
In second terminal window (to control robot's movement from the keyboard)
```
   $ roslaunch turtlebot_teleop keyboard_teleop.launch
```
In thierd terminal window (to control angles of the camera)
```
   $ rostopic pub /set_angle geometry_msgs/Vector3 "x: 0.0
     y: 0.0
     z: 0.0"
```
where
   - x - pitch [-90; +90], degree
   - y - yaw [-90; +90], degree
   - z - not used

If angles are more then the specified ranges, camera rotates to the closest value (to maximum or to minimum).

##Screenshot

![alt tag](https://cloud.githubusercontent.com/assets/2683284/12974443/b0bbb9f6-d0bc-11e5-8679-f7cc50bc75d2.png)
