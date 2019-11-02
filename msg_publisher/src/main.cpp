// This program publishes messages for the wheel ticks for a DIFF robot
// Reference to: http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29

#include <ros/ros.h>            // Most common public pieces of the ROS system
#include <std_msgs/String.h>    // This includes the std_msgs/String message, which resides in the std_msgs package.
#include <iostream>

int main(int argc, char** argv) {
    ros::init(argc, argv, "wheel_tick_msg_node"); // Initialize ROS. Specify the name of our node.
    ros::NodeHandle node_handle;    // Specify the name of our node.
    // We are going to be publishing a message of type "std_msgs/String"
    // Topic called "std_msgs/String"
    // Publishing queue
    ros::Publisher publisher = node_handle.advertise<std_msgs::String>("wt_msg", 10);
    ros::Rate loopRate(1);  // Frequency of repetition in Hz

    std_msgs::String msg;
    int left_wt  = 1000;    // Wheel ticks of left wheel
    int right_wt = 1100;

    while( ros::ok() ){
        msg.data = "L: " + std::to_string(left_wt) + "R: " + std::to_string(right_wt);
        publisher.publish(msg);

        left_wt++;
        right_wt++;
        ros::spinOnce();
        loopRate.sleep();
    }

    return EXIT_SUCCESS;
}
