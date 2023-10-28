#include <geometry_msgs/Twist.h>

#include <softPwm.h>
#include <vector>
#include <wiringPi.h>

#include "PWM.h"

#define L 0.120
#define R 0.024
#define MAX_SPEED 4.8332

enum Direction {
	FORWARD,
	BACKWARD
};

enum Motor {
	FRONT,
	LEFT,
	RIGHT
};

class DC_motor {
  private:
	int id_;

	int PWM_;
	int IN2_;
	int IN1_;

  public:
	DC_motor( int id ) {
		id_ = id;

		if ( id_ == 0 ) {
			PWM_ = 8;
			IN2_ = 9;
			IN1_ = 10;
		} else if ( id_ == 1 ) {
			PWM_ = 13;
			IN2_ = 12;
			IN1_ = 11;
		} else if ( id_ == 2 ) {
			PWM_ = 2;
			IN2_ = 3;
			IN1_ = 4;
		} else if ( id_ == 3 ) {
			PWM_ = 7;
			IN2_ = 6;
			IN1_ = 5;
		} else {
			PWM_ = 0;
			IN2_ = 0;
			IN1_ = 0;
		}
	}

	void turn( Direction dir ) {
		if ( dir == FORWARD ) {
			setPWM( IN1_, 4095, 0 );
			setPWM( IN2_, 0, 4095 );
		} else if ( dir == BACKWARD ) {
			setPWM( IN1_, 0, 4095 );
			setPWM( IN2_, 4095, 0 );
		} else {
			setPWM( IN1_, 0, 4095 );
			setPWM( IN2_, 0, 4095 );
		}
	}

	void set_speed( int speed ) {
		speed = (speed < 0 ) ? 0 : ( speed > 4095 ) ? 4095 : speed;
		setPWM( PWM_, 0, speed );
	}

	void print_info( float speed, Direction dir ) {
		ROS_INFO_STREAM( "motor " <<
			id_ << " " <<
			PWM_ << " " <<
			IN2_ << " " <<
			IN1_ << " " <<
			speed << " " <<
			dir
		);
	}

};

class Motor_hat {
  private:
	ros::Subscriber sub_;

	std::vector<DC_motor> motors_;

	void turn_motor( Motor id, float w ) {
		DC_motor* motor;
		motor = ( id == FRONT ) ? &motors_[1] :
			( id == LEFT ) ? &motors_[0] :
			&motors_[2];

		Direction dir = ( w >= 0 ) ? FORWARD : BACKWARD;

		float speed;
		speed = ( w < 0 ) ? -w : w;
		speed = ( speed > MAX_SPEED ) ? MAX_SPEED : speed;
		speed = 4096 * speed / (float)MAX_SPEED;

		motor->set_speed( speed );
		motor->turn( dir );

		motor->print_info( speed, dir );
	}

	void callback( const geometry_msgs::Twist &msg ) {
		ROS_INFO_STREAM( "cmd asserv " <<
			msg.linear.x << " " <<
			msg.linear.y << " " <<
			msg.linear.z << " " <<
			msg.angular.x << " " <<
			msg.angular.y << " " <<
			msg.angular.z
		);

		float x, y, w;
		x = msg.linear.x;
		y = msg.linear.y;
		w = msg.angular.z;

		float cste = sqrt(3) * 0.5;

		float w1, w2, w3;

		w1 = ( 0     * x + 1   * y - L * w ) / R;
		w2 = ( -cste * x - 0.5 * y - L * w ) / R;
		w3 = ( cste  * x - 0.5 * y - L * w ) / R;

		ROS_INFO_STREAM( "w " <<
			w1 << " " <<
			w2 << " " <<
			w3
		);

		turn_motor( FRONT, w1 );
		turn_motor( LEFT, w2 );
		turn_motor( RIGHT, w3 );
	}

  public:
	Motor_hat() {
		for ( unsigned int id = 0; id < 3; ++id ) {
			motors_.push_back( DC_motor( id ) );
		}

		initPWM( 0x60 );
		setPWMFreq( 1600 );

		ros::NodeHandle nh;
		sub_ = nh.subscribe( "cmd_vel_asserv", 10, &Motor_hat::callback, this );
	}
};
