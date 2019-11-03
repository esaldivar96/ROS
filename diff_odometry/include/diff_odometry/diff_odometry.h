/* Prototype of class Collage */

#ifndef DIFF_ODOM_H
#define DIFF_ODOM_H

    #include <ros/ros.h>
    #include <std_msgs/String.h>
    #include <tf/transform_broadcaster.h>
    #include <nav_msgs/Odometry.h>
    #include <iostream>

    void calculateOdometry(double delta_time, int wt_left, int wt_right);
    int findLeftDigits(std::string received_msg);
    void initializeGlovalVariables();
    void wt_msgCallback(const std_msgs::String& msg);

    const double _COUNTS_PER_REV = 4480.0; // wheel ticks per revolution
    const double _WHEEL_RADIUS = 0.05; // meters
    const double _WHEEL_PERIMETER = 2 * 3.14159265 * _WHEEL_RADIUS;
    const double _SEPARATION_BETWEEN_WHEELS = 0.2; // meters

    extern std::string received_msg;
    //////////////////////////////////////////////////////////////////////////// ODOM SETUP
    // Positions
    extern double x;    // Robot starts at the origin of the "odom" coordinate frame initially
    extern double y;
    extern double th;
    // Velocities
    extern double vx;   // 0.0 m/s in x
    extern double vy;   // 0.0 m/s in y
    extern double vth;  // 0.0 rad/s in theta

#endif
