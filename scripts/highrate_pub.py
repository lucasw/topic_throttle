#!/usr/bin/env python

import rospy

from sensor_msgs.msg import Imu

rospy.init_node('highrate_pub')

pub = rospy.Publisher('imu', Imu, queue_size=1)
rate = rospy.Rate(1000)

imu = Imu()
while not rospy.is_shutdown():
    pub.publish(imu)
    rate.sleep()
