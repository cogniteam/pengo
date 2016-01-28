/*
 * camera_movement.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: misha
 */
#include <camera_movement_controller/camera_movement.h>

	void CameraMovement::load_params (){
		if (not node.getParamCached ("base_vel", base_vel)){
			ROS_WARN ("base_vel is set by default to %f", base_vel);
		}
		if (not node.getParamCached ("gimbal_vel", gimbal_vel)){
			ROS_WARN ("gimbal_vel is set by default to %f", gimbal_vel);
		}
		if (not node.getParamCached ("base_angle_limit/min", base_angle_limit.first)){
			ROS_WARN ("base_angle_limit/min is set by default to %f", base_angle_limit.first);
		}
		if (not node.getParamCached ("base_angle_limit/max", base_angle_limit.second)){
			ROS_WARN ("base_angle_limit/max is set by default to %f", base_angle_limit.second);
		}
		if (not node.getParamCached ("gimbal_angle_limit/min", gimbal_angle_limit.first)){
			ROS_WARN ("gimbal_angle_limit/min is set by default to %f", gimbal_angle_limit.first);
		}
		if (not node.getParamCached ("gimbal_angle_limit/max", gimbal_angle_limit.second)){
			ROS_WARN ("gimbal_angle_limit/max is set by default to %f", gimbal_angle_limit.second);
		}
	}


	void CameraMovement::on_new_joint_state (sensor_msgs::JointState::Ptr new_state){
		for (int i = 0; i < new_state->name.size(); i++){
			if (new_state->name[i].compare("base_fork_joint") == 0){
				current_base_angle = new_state->position[i];
			}
			if (new_state->name[i].compare("fork_plate_joint") == 0){
				current_gimbal_angle = new_state->position[i];
			}
		}

		if (current_base_angle <= base_angle_limit.first and (not base_rotate_direction)){
			std_msgs::Float64 msg;
			msg.data = 0;
			base_vel_pub.publish (msg);
//			ROS_WARN ("base stop: limits are reached");
		}

		if (current_base_angle >= base_angle_limit.second and base_rotate_direction){
			std_msgs::Float64 msg;
			msg.data = 0;
			base_vel_pub.publish (msg);
//			ROS_WARN ("base stop: limits are reached");
		}



		if (base_rotate_direction and current_base_angle >= target_base_angle) {
			std_msgs::Float64 msg;
			msg.data = 0;
			base_vel_pub.publish (msg);
//			ROS_WARN ("base stop: target reached");
		}

		if ((not base_rotate_direction) and current_base_angle <= target_base_angle) {
			std_msgs::Float64 msg;
			msg.data = 0;
			base_vel_pub.publish (msg);
//			ROS_WARN ("base stop: target reached");
		}




		if (current_gimbal_angle <= gimbal_angle_limit.first and (not gimbal_rotate_direction)){
			std_msgs::Float64 msg;
			msg.data = 0;
			gimbal_vel_pub.publish (msg);
//			ROS_WARN ("gimbal stop: target reached");
		}

		if (current_gimbal_angle >= gimbal_angle_limit.second and gimbal_rotate_direction){
			std_msgs::Float64 msg;
			msg.data = 0;
			gimbal_vel_pub.publish (msg);
//			ROS_WARN ("gimbal stop: target reached");
		}

		if (gimbal_rotate_direction and current_gimbal_angle >= target_gimbal_angle){
			std_msgs::Float64 msg;
			msg.data = 0;
			gimbal_vel_pub.publish (msg);
//			ROS_WARN ("gimbal stop: target reached");
		}

		if ((not gimbal_rotate_direction) and current_gimbal_angle <= target_gimbal_angle){
			std_msgs::Float64 msg;
			msg.data = 0;
			gimbal_vel_pub.publish (msg);
//			ROS_WARN ("gimbal stop: target reached");
		}




	}

	void CameraMovement::on_new_base_angle (std_msgs::Float64::Ptr new_base_angle){
		if (target_base_angle == new_base_angle->data){
			return;
		}

		std_msgs::Float64 msg;
		msg.data = 0;
		target_base_angle = new_base_angle->data;
		if (target_base_angle > current_base_angle){
			msg.data = base_vel;
			base_rotate_direction = true;
		} else
			if (target_base_angle < current_base_angle){
				msg.data = -base_vel;
				base_rotate_direction = false;
			} else return;
		base_vel_pub.publish (msg);
	}

	void CameraMovement::on_new_gimbal_angle (std_msgs::Float64::Ptr new_gimbal_angle){
		if (target_gimbal_angle == new_gimbal_angle->data){
			return;
		}

		std_msgs::Float64 msg;
		msg.data = 0;
		target_gimbal_angle = new_gimbal_angle->data;
		if (target_gimbal_angle > current_gimbal_angle){
			msg.data = gimbal_vel;
			gimbal_rotate_direction = true;
		} else
			if (target_gimbal_angle < current_gimbal_angle){
				msg.data = -gimbal_vel;
				gimbal_rotate_direction = false;
			} else return;
		gimbal_vel_pub.publish (msg);
	}


	CameraMovement::CameraMovement (ros::NodeHandle node)
	: node (node)
	, base_vel (0.2)
	, gimbal_vel (0.2)
	, target_base_angle (0)
	, target_gimbal_angle (0)
	, current_base_angle (0)
	, current_gimbal_angle (0)
	, base_angle_limit (-M_PI/2, M_PI/2)
	, gimbal_angle_limit (-M_PI/2, M_PI/2)
	, base_rotate_direction (true)
	, gimbal_rotate_direction (true)
	{
		load_params ();
		joint_state_sub = node.subscribe ("/joint_states", 1,  &CameraMovement::on_new_joint_state, this);

		base_angle_sub = node.subscribe ("/base_angle", 1,  &CameraMovement::on_new_base_angle, this);
		gimbal_angle_sub = node.subscribe ("/gimbal_angle", 1,  &CameraMovement::on_new_gimbal_angle, this);

		base_vel_pub = node.advertise<std_msgs::Float64>("/stand/base_rotation/command", 1, false);
		gimbal_vel_pub = node.advertise<std_msgs::Float64>("/stand/gimbal_rotation/command", 1, false);


	}
