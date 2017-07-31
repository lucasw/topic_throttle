#include <nodelet/loader.h>
#include <ros/ros.h>
#include <string>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "imu_throttle");
  nodelet::Loader nodelet;
  nodelet::M_string remap(ros::names::getRemappings());
  nodelet::V_string nargv;
  std::string nodelet_name = ros::this_node::getName();
  nodelet.load(nodelet_name, "topic_throttle/NodeletThrottleImu", remap, nargv);
  ros::spin();
}

