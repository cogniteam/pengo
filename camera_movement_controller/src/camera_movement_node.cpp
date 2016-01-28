/*
 * camera_movement_node.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: misha
 */
#include <ros/ros.h>
#include <camera_movement_controller/camera_movement.h>



int main(int argc, char **argv) {
	ros::init(argc, argv, "camera_movement_node");
	ros::NodeHandle node ("~");
	CameraMovement camera_movement (node);
	ros::spin ();
    return (0);
}

