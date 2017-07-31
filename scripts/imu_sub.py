#!/usr/bin/env python

import rospy

from sensor_msgs.msg import Imu

def callback(data):
    global last_pub  # rate
    global start
    global period
    cur = rospy.Time.now()
    # elapsed = data.header.stamp - last_pub
    elapsed = cur - last_pub
    remaining = period - elapsed
    if remaining.to_sec() > 0:
        rospy.sleep(remaining.to_sec())
        return

    global count
    count += 1
    global pub
    pub.publish(data)
    # last_pub = data.header.stamp
    last_pub = cur
       # rate.sleep()

rospy.init_node('imu_sub')

count = 0
last_pub = rospy.Time.now()
start = rospy.Time.now()
period = 0.0
rate = rospy.get_param("~rate", 0.0)
if (rate <= 0.0):
    rate = 1.0
period = rospy.Duration(1.0 / rate)

sub = rospy.Subscriber("imu", Imu, callback, queue_size=1)
pub = rospy.Publisher("imu_throttle", Imu, queue_size=2)
rospy.spin()
