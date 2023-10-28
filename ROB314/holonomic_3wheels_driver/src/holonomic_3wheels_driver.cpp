#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "motor_hat.hpp"
#include "PID.hpp"

int main( int argc, char** argv ) {
	ros::init( argc, argv, "holonomic_3wheels_driver" );

	float dt = 0.1;

	Motor_hat hat;
	PID pid( 0.0, 0.0, 0.0, dt );

	ros::Rate r( 1.0 / dt );

	geometry_msgs::Twist odom;

	while( ros::ok() ) {
		ros::spinOnce();
		pid.compute( odom );
		r.sleep();
	}

	return 0;
}
