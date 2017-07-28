#!/usr/bin/env python

import rospy

from sensor_msgs.msg import Imu

def callback(data):
    global count
    count += 1
    global pub
    pub.publish(data)
    global rate
    rate.sleep()

rospy.init_node('imu_sub')

# sub = rospy.Subscriber("imu_throttle", Imu, callback)
count = 0
rate = rospy.Rate(50)
sub = rospy.Subscriber("imu", Imu, callback, queue_size=3)
pub = rospy.Publisher("imu_throttle", Imu, queue_size=2)
rospy.spin()
