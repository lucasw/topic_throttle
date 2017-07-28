#!/usr/bin/env python

import rospy

from sensor_msgs.msg import Imu

def callback(data):
    global last_pub  # rate
    global start
    period = rospy.Duration(1.0)
    elapsed = data.header.stamp - last_pub
    remaining = period - elapsed
    rospy.loginfo(str(elapsed.to_sec()) + ' ' + str(period.to_sec()) + ' ' +
                  str(remaining.to_sec()))
    rospy.loginfo(data.header.stamp.to_sec() - start.to_sec())
    rospy.loginfo(last_pub.to_sec() - start.to_sec())
    rospy.loginfo(rospy.Time.now().to_sec() - start.to_sec())
    if remaining.to_sec > 0:
        rospy.sleep(remaining.to_sec())
        return

    global count
    count += 1
    global pub
    pub.publish(data)
    last_pub = data.header.stamp
       # rate.sleep()

rospy.init_node('imu_sub')

# sub = rospy.Subscriber("imu_throttle", Imu, callback)
count = 0
last_pub = rospy.Time.now()
start = rospy.Time.now()
sub = rospy.Subscriber("imu", Imu, callback, queue_size=3)
pub = rospy.Publisher("imu_throttle", Imu, queue_size=2)
rospy.spin()
