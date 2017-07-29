#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

int count = 0;
ros::Publisher pub;
ros::Time last_pub;

void callback(const sensor_msgs::Imu::ConstPtr& msg)
{
  ros::Time cur = ros::Time::now();
  ros::Duration period(1.0);
  ros::Duration elapsed = cur - last_pub;
  ros::Duration remaining = period - elapsed;
  if (remaining > 0)
  {
    remaining.sleep();
    return;
  }
  pub.publish(msg);
  last_pub = cur;

  count += 1;
  if (count % 50 == 0)
  {
    //ROS_INFO_STREAM(msg);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "imu_sub");
  ros::NodeHandle nh;
  last_pub = ros::Time::now();
  pub = nh.advertise<sensor_msgs::Imu>("imu_throttle", 2);
  ros::Subscriber sub = nh.subscribe("imu", 1, callback);
  ros::spin();
}
