#include "ros/ros.h"
#include "std_msgs/String.h"

void rssiCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Received: %s", msg->data.c_str());

    // Process the received message, e.g., extract data and perform actions
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "car_subscriber");
    ros::NodeHandle nh;

    ros::Subscriber rssi_subscriber = nh.subscribe("ble_rssi", 10, rssiCallback);

    ros::spin();

    return 0;
}
