# Instalation
Install turtlebot_simulator package
```
   $ sudo apt-get install ros-indigo-turtlebot-simulator
   $ sudo apt-get install ros-indigo-turtlebot-apps ros-indigo-turtlebot-rviz-launchers
```
Copy Turtlebot project from the GitHub
```
   $ cd
   $ mkdir -p workspace/src
   $ cd workspace/src
   $ git clone https://github.com/cogniteam/turtlebot.git
```
Compile Turtlebot project
```
   $ cd ~/workspace
   $ catkin_make
```


# Running
In first terminal window (to run environment)
```
   $ source ~/workspace/devel/setup.bash
   $ roslaunch turtlebot turtlebot_world.launch
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
