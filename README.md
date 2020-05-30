## Home Service Robot - Udacity Robotics ND ##

This project we've put all together since previous projects in Robotics ND.
Since, building a world in gazebo, creating a map of it, test AMCL to localize a robot using particle filter.
I have use my own robot to accomplish each of the tasks required.
The simulation shows how the robot could be used to perform a common pick&place an object. In this project picking is not implemented.

1) Use the Building Editor tool in Gazebo to build a virtual environment.
2) Teleoperate your robot and test SLAM.
3) Use the ROS navigation stack to set 2D Nav Goals to your robot.
4) Write a `pick_objects` node that sends goals to ROS navigation stack.
5) Write an `add_markers` node to send virtual marks to `map` frame in rviz.

** Dependeces **

This repo includes official ROS packages that you can use in your own world and robot, but it's given for make easy to use with the well known `turtlebot` platform: `gmapping`, `turtlebot_teleop`, `turtlebot_rviz_launchers`, and `turtlebot_gazebo`.

gmapping: to perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.

turtlebot_teleop: to control your robot using keyboard commands.

turtlebot_rviz_launchers: to load a very useful rviz configuration, that shows you the robot model, trajectories, map, particles of poses etc.

turtlebot_gazebo: to bring to life a turtlebot in gazebo.

** How to run it **

Clone this repo into your `catkin_ws/src/` folder: 
`git clone https://github.com/diegoavillegasg/home-service-robot`

Build workspace: 
`cd ~/catkin_ws/`
`catkin_make`

Load current workspace vars: `source dev/setup.bash`

Move to `scripts` folder: 
`cd src/scripts/`

To try mapping:
`./my_robot_test_slam.sh`

To see the final result:
`./my_robot_home_service.sh`

![](home_service_robot.gif)

