cmake_minimum_required( VERSION 3.0.2 )
project( holonomic_3wheels_driver )

find_package( catkin REQUIRED COMPONENTS
	roscpp
	geometry_msgs
)

catkin_package()

include_directories( ${catkin_INCLUDE_DIRS} )

add_library( PWM src/PWM.cpp )

find_library( wiringPi REQUIRED )

add_executable( driver_node
	src/holonomic_3wheels_driver.cpp
)

target_link_libraries( driver_node
	${catkin_LIBRARIES}
	PWM
	wiringPi
)
