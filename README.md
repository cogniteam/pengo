# Instalation
1. Install turtlebot_simulator package
```
   $ sudo apt-get install ros-indigo-turtlebot-simulator
   $ sudo apt-get install ros-indigo-turtlebot-apps ros-indigo-turtlebot-rviz-launchers
```
2. Copy Gazebo world from the GitHub
```
   $ mkdir -p workspace/src
   $ cd workspace/src
   $ git clone https://github.com/cogniteam/turtlebot.git
   $ cd ..
   $ catkin_make
   $ source devel/setup.bash
```
3. Update urdf file to use Hokuyo lidar
```
   $ cd src/turtlebot/stacks
   $ sudo mv circles.urdf.xacro /opt/ros/indigo/share/turtlebot_description/urdf/stacks/circles.urdf.xacro
   $ sudo mv hexagons.urdf.xacro /opt/ros/indigo/share/turtlebot_description/urdf/stacks/hexagons.urdf.xacro
```
## Running
1. In first terminal window
```
   $ cd ..
   $ roslaunch launch/turtlebot_world.launch
```
2. In second terminal window
```
   $ cd ..
   $ roslaunch turtlebot_teleop keyboard_teleop.launch
```

## NOTES
In a launch file ```turtlebot_world.launch``` you can choose the following ```base``` and ```stack``` parameters combinations:
1. ```kobuki``` ```hexagons```
2. ```roomba``` ```circles```
