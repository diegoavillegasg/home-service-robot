#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <complex>
#include <std_msgs/UInt8.h>


float pickUp[3] = {-2.0,-2.0, 1.0};
float dropOf[3] = { 3.0, 1.0, 1.0};
float threshold[2] = {0.3, 0.01};

uint8_t robotState = 0;
bool atInitPose = true;
bool atPickUp = false;
bool atDropOf = false;
bool pickUpDoneOK = false;
bool dropOffDoneOK = false;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  //doing pick up
  if (std::abs(pickUp[0] - msg->pose.pose.position.x) < threshold[0] &&
    std::abs(pickUp[1] - msg->pose.pose.position.y) < threshold[0] &&
    std::abs(pickUp[2] - msg->pose.pose.orientation.w) < threshold[1]) {
      if (!atPickUp) { atPickUp = true; }
  }
  else { atPickUp = false; }

  //doing drop off
  if (std::abs(dropOf[0] - msg->pose.pose.position.x) < threshold[0] &&
    std::abs(dropOf[1] - msg->pose.pose.position.y) < threshold[0] &&
    std::abs(dropOf[2] - msg->pose.pose.orientation.w) < threshold[1]) {
      if (!atDropOf) { atDropOf = true; }      
    }
  else { atDropOf = false; }
}

void poseCallback(const std_msgs::UInt8::ConstPtr& msg) {
  robotState = msg->data;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //ros::Subscriber odom_subs = n.subscribe("odom", 1, odomCallback);
  ros::Subscriber pose_subs = n.subscribe("/my_robot_pose", 1, poseCallback);
  

  // Set our shape type to be a cylinder
  uint32_t shape = visualization_msgs::Marker::CYLINDER;
  
  while (ros::ok())
  {
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    visualization_msgs::Marker marker;

    marker.header.frame_id = "map";

    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;
    marker.type = shape;

    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0; // alpha should be diff to zero

    marker.lifetime = ros::Duration();


    if (robotState==0) { //(atInitPose && !atPickUp ) {
      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
      marker.pose.position.x =  pickUp[0];
      marker.pose.position.y = pickUp[1];
      marker.pose.orientation.w = pickUp[2];
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;

      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      // ROS_INFO("Object is displayed in the pickup zone");
    }

    if (robotState == 1) { // ( atPickUp && !pickUpDoneOK ) {
      marker.action = visualization_msgs::Marker::DELETE;
      // ROS_INFO("Object's gonna be tranported to the drop off zone");
      marker_pub.publish(marker);
      ros::Duration(5).sleep();
      pickUpDoneOK = true;
      atInitPose = false;
    }

    if (robotState == 2) { // (atDropOf && !dropOffDoneOK) {
      marker.pose.position.x = dropOf[0];
      marker.pose.position.y =  dropOf[1];
      marker.pose.orientation.w =  dropOf[2];
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      ros::Duration(5).sleep();
      // ROS_INFO("Object is released at the drop off zone");
      dropOffDoneOK = true;
      return 0;
    }    

    
    ros::spinOnce();
  }
}
