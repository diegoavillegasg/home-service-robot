#!/bin/sh
path=`rospack find "my_robot"`
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$path/worlds/project1.world " &
sleep 5
xterm -e " roslaunch turtlebot_navigation amcl_demo.launch " &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5
xterm -e " rosrun add_markers add_markers " &