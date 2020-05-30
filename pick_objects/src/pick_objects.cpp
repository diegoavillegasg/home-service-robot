#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/UInt8.h>

float pickUp[3] = {-2.0,-2.0, 1.0};
float dropOf[3] = { 3.0, 1.0, 1.0};


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher pose_pub = n.advertise<std_msgs::UInt8>("/my_robot_pose", 1);
  MoveBaseClient ac("move_base", true);

  while(!ac.waitForServer(ros::Duration(5.0))) {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  // pick up zone
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = pickUp[0];
  goal.target_pose.pose.position.y = pickUp[1];
  goal.target_pose.pose.orientation.w = pickUp[2];

  ROS_INFO("Sending a goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {

    ROS_INFO("yuhoop, the base have reached to pick up zone");
    std_msgs::UInt8 msg1;
    msg1.data = 1;
    pose_pub.publish(msg1);
    ros::Duration(5).sleep();

    // drop off zone
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = dropOf[0];
    goal.target_pose.pose.position.y =  dropOf[1];
    goal.target_pose.pose.orientation.w = dropOf[2];

    ac.sendGoal(goal);

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
      ROS_INFO("yuhoop, the base have reached to drop off zone");
      std_msgs::UInt8 msg2;
      msg2.data = 2;
      pose_pub.publish(msg2);
      ros::Duration(5).sleep();
    }
    else
      ROS_INFO("The base failed to move to drop off zone");
  }
  else
    ROS_INFO("The base failed to move to pick up zone");
  return 0;
}