# Instalation
Install turtlebot_simulator package
```
   $ sudo apt-get install ros-indigo-turtlebot-simulator
   $ sudo apt-get install ros-indigo-turtlebot-apps ros-indigo-turtlebot-rviz-launchers
```
Copy Gazebo world from the GitHub
```
   $ mkdir -p workspace/src
   $ cd workspace/src
   $ git clone https://github.com/cogniteam/turtlebot.git
   $ cd ..
   $ catkin_make
   $ source devel/setup.bash
```

## Running
In first terminal window
```
   $ roslaunch turtlebot turtlebot_world.launch
```
In second terminal window
```
   $ roslaunch turtlebot_teleop keyboard_teleop.launch
```

## NOTES
In a launch file ```turtlebot_world.launch``` you can choose the following ```base```, ```stack``` and ```3d_sensor``` parameters combinations:

1. ```kobuki``` ```hexagons``` ```kinect```
2. ```kobuki``` ```hexagons``` ```asus_xtion_pro```
3. ```kobuki``` ```hexagons``` ```realsense```
4. ```roomba``` ```circles``` ```kinect```
5. ```roomba``` ```circles``` ```asus_xtion_pro```
