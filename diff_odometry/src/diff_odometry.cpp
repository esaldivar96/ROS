#include "../include/diff_odometry/diff_odometry.h"

void calculateOdometry(double delta_time, int wt_left, int wt_right) {

    //////////////////////////////////////////////////////////////////////////// Obtain distance traveled
    double distance_left = (_WHEEL_PERIMETER * (double)wt_left) / _COUNTS_PER_REV;
    double distance_right = (_WHEEL_PERIMETER * (double)wt_right) / _COUNTS_PER_REV;
    double distance_robot = (distance_left + distance_right) / 2.0;    // meters

    //////////////////////////////////////////////////////////////////////////// Obtain new positions
    x = x + distance_robot * cos(th);
    y = y + distance_robot * sin(th);
    th = th + ((distance_right - distance_left) / _SEPARATION_BETWEEN_WHEELS);

    //////////////////////////////////////////////////////////////////////////// Obtain velocities traveled
    double v_left = distance_left / delta_time;
    double v_right = distance_right / delta_time;
    double v = distance_robot / delta_time;

    //////////////////////////////////////////////////////////////////////////// Obtain new velocities
    vx = v * cos(th);
    vy = v * sin(th);
    vth = ((v_right - v_left) / _SEPARATION_BETWEEN_WHEELS);
}

int findLeftDigits(std::string received_msg) {
    int left_c = 0;
    bool has_left_started = false;

    for(int i = 0; i < received_msg.size(); i++) {
        if(has_left_started == true) {
            if(received_msg[i] == 'R') {
                break;
            }
            left_c++;
        }

        if(received_msg[i] == ' ') {
            has_left_started = true;
        }
    }

    return left_c;
}

void initializeGlovalVariables() {
    received_msg = "";
    // Positions
    x  = 0.0;    // Robot starts at the origin of the "odom" coordinate frame initially
    y  = 0.0;
    th = 0.0;
    // Velocities
    vx  = 0.0;   // 0.0 m/s in x
    vy  = 0.0;   // 0.0 m/s in y
    vth = 0.0;   // 0.0 rad/s in theta
}

void wt_msgCallback(const std_msgs::String& msg) {
    received_msg = msg.data.c_str();
}
