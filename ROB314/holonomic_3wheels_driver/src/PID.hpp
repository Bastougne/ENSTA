#include <geometry_msgs/Twist.h>

class Vec3 {
  public:
	float x, y, z;

	Vec3() {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vec3( float x1, float y1, float z1 ) {
		x = x1;
		y = y1;
		z = z1;
	}

	Vec3( const Vec3 &vec ) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	Vec3 operator+=( const Vec3 &vec ) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vec3 operator-=( const Vec3 &vec ) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vec3 operator+( const Vec3 &vec ) {
		Vec3 v = *this;
		return v += vec;
	}

	Vec3 operator-( const Vec3 &vec ) {
		Vec3 v = *this;
		return v -= vec;
	}

	Vec3 operator*( float c ) {
		return Vec3( this->x * c, this->y * c, this->z * c );
	}

	Vec3 operator/( float c ) {
		return Vec3( this->x / c, this->y / c, this->z / c );
	}

	geometry_msgs::Twist Vec2Twist() {
		geometry_msgs::Twist twist;
		twist.linear.x = this->x;
		twist.linear.y = this->y;
		twist.angular.z = this->z;
		return twist;
	}
};

Vec3 Twist2Vec( const geometry_msgs::Twist &twist ) {
	return Vec3( twist.linear.x, twist.linear.y, twist.angular.z );
}

class PID {
  private:
	float Kp_, Ki_, Kd_;
	float dt_;

	Vec3 integral_;
	Vec3 prev_err_;

	ros::Subscriber cmd_sub_, odom_sub_;
	ros::Publisher pub_;

	geometry_msgs::Twist cmd, odom;

	void cmd_callback( const geometry_msgs::Twist &msg ) {
		ROS_INFO_STREAM( "cmd " <<
			msg.linear.x << " " <<
			msg.linear.y << " " <<
			msg.linear.z << " " <<
			msg.angular.x << " " <<
			msg.angular.y << " " <<
			msg.angular.z
		);

		cmd = msg;
	}

	void odom_callback( const geometry_msgs::Twist &msg ) {
		ROS_INFO_STREAM( "odom " <<
			msg.linear.x << " " <<
			msg.linear.y << " " <<
			msg.linear.z << " " <<
			msg.angular.x << " " <<
			msg.angular.y << " " <<
			msg.angular.z
		);

		odom = msg;
	}

  public:
	PID( float Kp, float Ki, float Kd, float dt ) {
		Kp_ = Kp;
		Ki_ = Ki;
		Kd_ = Kd;
		dt_ = dt;

		integral_ = Vec3();
		prev_err_ = Vec3();

		ros::NodeHandle nh;
		cmd_sub_ = nh.subscribe( "cmd_vel", 10, &PID::cmd_callback, this );
		odom_sub_ = nh.subscribe( "odom", 10, &PID::odom_callback, this );
		pub_ = nh.advertise<geometry_msgs::Twist>( "cmd_vel_asserv", 10 );
	}

	void compute( const geometry_msgs::Twist &odom1 ) {
		Vec3 err = Twist2Vec( cmd ) - Twist2Vec( odom1 ) / dt_;
		Vec3 derivative;

		integral_ += err * dt_;
		derivative = ( err - prev_err_ ) / dt_;

		Vec3 out = err * Kp_ + integral_ * Ki_ + derivative * Kd_;
		prev_err_ = err;

		geometry_msgs::Twist cmd_corr = ( Twist2Vec( cmd ) + out ).Vec2Twist();

		pub_.publish( cmd_corr );
	}
};
