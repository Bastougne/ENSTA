#define Z_MOUCH 0.0725
#define Y_MOUCH 0.025
#define X_MOUCH 0.05

#define GRIPPER_OFFSET 0.01

#define OPEN_GRIPPER 1
#define CLOSE_GRIPPER 0

#include <string>
#include <iostream>

#include "ros/ros.h"
#include "moveit/move_group_interface/move_group_interface.h"
#include "moveit/planning_scene_interface/planning_scene_interface.h"

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <std_srvs/Trigger.h>

#include <dynamixel_workbench_msgs/DynamixelCommand.h>
#include <dynamixel_workbench_toolbox/dynamixel_workbench.h>

#include <sensor_msgs/JointState.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/convert.h>

#include "tf/LinearMath/Transform.h"

#include <math.h>
#include <unistd.h>

void gripperCommand(bool order, ros::ServiceClient& serviceClient)
{
    dynamixel_workbench_msgs::DynamixelCommand gripCommand;

    gripCommand.request.id = 7;
    gripCommand.request.addr_name = "Goal_Position";

    if(order)
    {
        //Hardware value
        gripCommand.request.value = 770;
    }
    else
    {
        //Hardware value - To be set accordingly to the object to grab (no force control !)
        gripCommand.request.value = 450;
    }
    

    if(serviceClient.call(gripCommand))
    {
        ROS_INFO("Gripper order sent !");
    }

    ros::Duration(1.0).sleep();
    ROS_INFO("Gripper ready!");
}

void dynamixelExecuteTrajectory(trajectory_msgs::JointTrajectory& trajectoryGoal, ros::Publisher& trajectoryPublisher, ros::ServiceClient& executionServer, ros::Rate& loopRate)
{
    trajectoryPublisher.publish(trajectoryGoal);
    ros::spinOnce();
    loopRate.sleep();

    std_srvs::Trigger trigger;

    if(executionServer.call(trigger))
    {
        ROS_INFO("Initialisation sent !");
    }

    //The delay must be increased/decreased according to the planned displacement
    ros::Duration(5.0).sleep();
    ROS_INFO("Gripper ready!");
}

void setMarkers(ros::Publisher& marker_pub)
{
    ROS_INFO("Set the position of the object to grab : ");

    double x,y;
    
    std::cout << "Set x position : " << std::endl;
    std::cin >> x;
    std::cout << "Set y position : " << std::endl;
    std::cin >> y;

    //Initialisation
    visualization_msgs::Marker marker;

    //Set the frame ID and timestamp
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time::now();

    //Set the namespace and id of the marker
    marker.ns = "my_namespace";
    marker.id = 0;

    //Set the marker type
    uint32_t shape = visualization_msgs::Marker::CUBE;
    marker.type = shape;

    //Set the marker action
    marker.action = visualization_msgs::Marker::ADD;

    //Set the pose of the marker
    marker.pose.position.x = x;
    marker.pose.position.y = y;
    marker.pose.position.z = Z_MOUCH/2;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    //Set the scale of the marker
    marker.scale.x = X_MOUCH;
    marker.scale.y = Y_MOUCH;
    marker.scale.z = Z_MOUCH;

    //Set the color of the marker
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker_pub.publish(marker);
}

int main(int argc, char **argv)
{   
    //ROS Setup
    ros::init(argc, argv, "robot_arm_interface");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    //Dynamixel interface - Trajectories
    ros::Publisher dynamixelPublisherTraj = node_handle.advertise<trajectory_msgs::JointTrajectory>("dynamixel_workbench/joint_trajectory",10);
    ros::ServiceClient dynamixelServiceTraj = node_handle.serviceClient<std_srvs::Trigger>("dynamixel_workbench/execution");
    ros::Rate loopRate(10);

    //Dynamixel interface - Positions
    ros::ServiceClient dynamixelServicePos = node_handle.serviceClient<dynamixel_workbench_msgs::DynamixelCommand>("dynamixel_workbench/dynamixel_command");

    //RViz interface - Objects - Marker needs to be added on RViz !
    //ros::Publisher marker_pub = node_handle.advertise<visualization_msgs::Marker>("visualization_marker", 10);

    //Moveit interface Setup
    static const std::string PLANNING_GROUP = "robot_arm";
    moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

    const robot_state::JointModelGroup* joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

    //Visualization - RvizVisualToolsGui panel needs to be added on RViz !
    namespace rvt = rviz_visual_tools;
    moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
    visual_tools.deleteAllMarkers();
    visual_tools.loadRemoteControl();

    //Markers - MarkerArray needs to be added on RViz !
    Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
    text_pose.translation().z() = 1.75;
    visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);

    visual_tools.trigger();
    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to start !");

    //MoveGroupInterface Initialisation
    moveit::planning_interface::MoveGroupInterface::Plan plan;

    //Go to the default pose
    ROS_INFO("== Initialisation ==");

    std::vector<double> joint_group_positions = {0.0,0.0,0.0,0.0,0.0,0.0};
    move_group.setJointValueTarget(joint_group_positions);
    bool success = (move_group.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Initialisation %s", success ? "" : "FAILED");

    //Execute trajectory on dynamixel side
    dynamixelExecuteTrajectory(plan.trajectory_.joint_trajectory, dynamixelPublisherTraj, dynamixelServiceTraj, loopRate);

    //Close Gripper
    gripperCommand(0, dynamixelServicePos);

    ROS_INFO("== Compute trajectory ==");

    //Define target pose
    geometry_msgs::Pose targetPose = move_group.getCurrentPose().pose;

    //DEBUG
    //std::cout<<targetPose<<std::endl;

    targetPose.position.x -= GRIPPER_OFFSET;
    targetPose.position.y += 0.1;
    targetPose.position.z += GRIPPER_OFFSET/2;

    //DEBUG
    //std::cout<<targetPose<<std::endl;

    //Compute trajectory 
    move_group.setPoseTarget(targetPose);
    success = (move_group.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Computing trajectory %s", success ? "" : "FAILED");

    // Visualize the trajectory in RViz
    visual_tools.deleteAllMarkers();
    visual_tools.publishText(text_pose, "Joint Space Goal", rvt::WHITE, rvt::XLARGE);
    visual_tools.publishTrajectoryLine(plan.trajectory_, joint_model_group);
    visual_tools.trigger();
    visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window once the trajectory appears in RVIz and is validated");

    //DEBUG
    //std::cout<<plan.trajectory_.joint_trajectory<<std::endl;

    ROS_INFO("== Execute trajectory ==");

    //Execute trajectory on dynamixel side
    dynamixelExecuteTrajectory(plan.trajectory_.joint_trajectory, dynamixelPublisherTraj, dynamixelServiceTraj, loopRate);

    //Open gripper
    gripperCommand(1,dynamixelServicePos);

    ros::Duration(5.0).sleep();

    //Close gripper
    gripperCommand(0,dynamixelServicePos);

    ros::Duration(5.0).sleep();

    //Open gripper
    gripperCommand(1,dynamixelServicePos);

    //Go to the shutdown pose
    ROS_INFO("== Shutting down ==");

    //Close gripper
    gripperCommand(0,dynamixelServicePos);
    
    //Return to sleep position
    joint_group_positions = {0.0,0.0,0.0,0.0,M_PI/6,0.0};
    move_group.setJointValueTarget(joint_group_positions);
    success = (move_group.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    ROS_INFO("Shutting down %s", success ? "" : "FAILED");

    //Execute trajectory on dynamixel side
    dynamixelExecuteTrajectory(plan.trajectory_.joint_trajectory, dynamixelPublisherTraj, dynamixelServiceTraj, loopRate);

    ROS_INFO("Shut down complete !");
    
    return 0;
}
