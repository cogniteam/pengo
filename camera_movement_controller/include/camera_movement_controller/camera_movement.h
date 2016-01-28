/*
 * camera_movement.h
 *
 *  Created on: Jan 28, 2016
 *      Author: misha
 */

#ifndef INCLUDE_CAMERA_MOVEMENT_CONTROLLER_CAMERA_MOVEMENT_H_
#define INCLUDE_CAMERA_MOVEMENT_CONTROLLER_CAMERA_MOVEMENT_H_

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>


class CameraMovement {
private:
	ros::NodeHandle node;

	ros::Subscriber joint_state_sub;
	ros::Subscriber base_angle_sub;
	ros::Subscriber gimbal_angle_sub;

	ros::Publisher base_vel_pub;
	ros::Publisher gimbal_vel_pub;

	double base_vel; // rad/sec
	double gimbal_vel; // rad/sec

	double target_base_angle; // rad
	double target_gimbal_angle; // rad

	bool base_rotate_direction;
	bool gimbal_rotate_direction;

	double current_base_angle;
	double current_gimbal_angle;

	std::pair <double, double> base_angle_limit; // min/max angles in rad
	std::pair <double, double> gimbal_angle_limit; // min/max angles in rad
public:
	void load_params ();
	void on_new_joint_state (sensor_msgs::JointState::Ptr new_state);
	void on_new_base_angle (std_msgs::Float64::Ptr new_base_angle);
	void on_new_gimbal_angle (std_msgs::Float64::Ptr new_gimbal_angle);
	CameraMovement (ros::NodeHandle node);
};



#endif /* INCLUDE_CAMERA_MOVEMENT_CONTROLLER_CAMERA_MOVEMENT_H_ */
