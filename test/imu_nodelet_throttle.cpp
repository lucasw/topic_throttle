#include <nodelet_topic_tools/nodelet_throttle.h>
#include <sensor_msgs/Imu.h>
#include <pluginlib/class_list_macros.h>

// https://github.com/jon-weisz/camera_throttler_nodelets/blob/master/src/camera_throttler_nodelets/init.cpp

namespace topic_throttle {
typedef nodelet_topic_tools::NodeletThrottle<sensor_msgs::Imu> NodeletThrottleImu;
}
PLUGINLIB_EXPORT_CLASS(topic_throttle::NodeletThrottleImu, nodelet::Nodelet)
