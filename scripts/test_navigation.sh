#!/bin/sh
# turtlebot in our world
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/worlds/project1.world " &
sleep 5
xterm -e " roslaunch turtlebot_navigation amcl_demo.launch " &
speed 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &