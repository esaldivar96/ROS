// Publisher and subsriber in a single node: https://gist.github.com/PrieureDeSion/77c109a074573ce9d13da244e5f82c4d
// nav_msgs: https://answers.ros.org/question/241602/get-odometry-from-wheels-encoders/
// nav_msgs: http://wiki.ros.org/navigation/Tutorials/RobotSetup/Odom
// nav_msgs: https://www.youtube.com/watch?v=I_5leJK8vhQ&t=382s
// calculations: https://www.youtube.com/watch?v=oeTxkIWdd9I
// dc motor: https://www.pololu.com/product/4754
// for cartographer: https://google-cartographer-ros.readthedocs.io/en/latest/going_further.html

#include "../include/diff_odometry/diff_odometry.h"

std::string received_msg;
//////////////////////////////////////////////////////////////////////////// ODOM SETUP
// Positions
double x;    // Robot starts at the origin of the "odom" coordinate frame initially
double y;
double th;
// Velocities
double vx;   // 0.0 m/s in x
double vy;   // 0.0 m/s in y
double vth;  // 0.0 rad/s in theta

int main(int argc, char **argv) {
    //////////////////////////////////////////////////////////////////////////// ROS SETUP
    ros::init(argc, argv, "odom_publisher");
    ros::NodeHandle nodeHandle;

    ros::Publisher publisher = nodeHandle.advertise<nav_msgs::Odometry>("odom_msg", 10);
    ros::Subscriber subscriber = nodeHandle.subscribe("wt_msg",10,wt_msgCallback);
    tf::TransformBroadcaster odom_broadcaster;

    nav_msgs::Odometry odom;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    geometry_msgs::Quaternion odom_quat;

    geometry_msgs::TransformStamped odom_trans;

    ros::Rate loopRate(1);  // Frequency of repetition in Hz

    initializeGlovalVariables();

    ros::Time current_time = ros::Time::now();
    ros::Time last_time = ros::Time::now();
    int left_c = 0;
    int wt_left  = 0;
    int wt_right = 0;

    while( ros::ok() ){
        ros::spinOnce(); // Checks for received messages
        current_time = ros::Time::now();
        //std::cout<<received_msg<<std::endl;

        if(received_msg[0] == 'L') {
            left_c   = findLeftDigits(received_msg);
            wt_left  = std::stoi(received_msg.substr(3,left_c));
            wt_right = std::stoi(received_msg.substr(6 + left_c, received_msg.size() - 1));
            left_c   = 0;
            std::cout<<"Left value: "<<wt_left<<" Right value: "<<wt_right<<std::endl;
        }

        //////////////////////////////////////////////////////////////////////// Odometry
        calculateOdometry((current_time - last_time).toSec(), wt_left, wt_right);
        odom.header.stamp = current_time;
        //set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = 0.0;
        odom_quat = tf::createQuaternionMsgFromYaw(th);
        odom.pose.pose.orientation = odom_quat;
        //set the velocity
        odom.twist.twist.linear.x = vx;
        odom.twist.twist.linear.y = vy;
        odom.twist.twist.angular.z = vth;

        //////////////////////////////////////////////////////////////////////// Trandform
        geometry_msgs::TransformStamped odom_trans;
        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "odom";
        odom_trans.child_frame_id = "base_link";
        odom_trans.transform.translation.x = x;
        odom_trans.transform.translation.y = y;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        //publish the message
        odom_broadcaster.sendTransform(odom_trans);
        publisher.publish(odom);

        last_time = current_time;
        loopRate.sleep();
    }

    return EXIT_SUCCESS;
}

//void calculateOdometry(ros::Time delta_time, int wt_left, int wt_right) {
    //distance_left =
//}











//
