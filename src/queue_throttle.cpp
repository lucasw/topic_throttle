#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <topic_tools/shape_shifter.h>

namespace topic_throttle
{

class QueueThrottle : public nodelet::Nodelet
{
  void callback(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event);

  ros::Subscriber sub_;
  ros::Publisher pub_;
  ros::Time last_pub_;
  ros::Duration period_;

public:
  /// QueueThrottle();
  virtual void onInit();
};

void QueueThrottle::onInit()
{
  last_pub_ = ros::Time::now();
  double rate = 0.0;
  ros::param::get("~rate", rate);
  if (rate <= 0.0)
  {
    // TODO(lucasw) maybe rate 0.0 should be no throttling at all?
    ROS_WARN_STREAM("invalid rate " << rate << ", setting to 1.0");
    rate = 1.0;
  }
  period_ = ros::Duration(1.0 / rate);
  ROS_INFO_STREAM("rate " << rate << " " << period_);
  sub_ = getNodeHandle().subscribe("topic", 1, &QueueThrottle::callback, this);
}

void QueueThrottle::callback(const ros::MessageEvent<topic_tools::ShapeShifter>& msg_event)
{
  ros::Time cur = ros::Time::now();
  ros::Duration elapsed = cur - last_pub_;
  ros::Duration remaining = period_ - elapsed;
  if (remaining.toSec() > 0)
  {
    remaining.sleep();
    return;
  }
  boost::shared_ptr<topic_tools::ShapeShifter const> const &msg = msg_event.getConstMessage();
  if (pub_.getTopic() == std::string())
    pub_ = msg->advertise(getNodeHandle(), "topic_throttle", 2);

  pub_.publish(msg);
  last_pub_ = cur;
}

};  // namespace topic_throttle

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(topic_throttle::QueueThrottle, nodelet::Nodelet)
