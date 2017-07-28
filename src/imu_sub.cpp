#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

int count = 0;

void callback(const sensor_msgs::Imu::ConstPtr& msg)
{
  count += 1;
  if (count % 50 == 0)
  {
    ROS_INFO_STREAM(msg);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "imu_sub");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("imu", 10, callback);
  ros::spin();
}
