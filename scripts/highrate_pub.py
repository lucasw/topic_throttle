#!/usr/bin/env python

import rospy

from sensor_msgs.msg import Imu

rospy.init_node('highrate_pub')

pub = rospy.Publisher('imu', Imu, queue_size=1)
rate = rospy.Rate(1000)

count = 0
imu = Imu()
while not rospy.is_shutdown():
    imu.header.stamp = rospy.Time.now()
    imu.header.frame_id = str(count)
    pub.publish(imu)
    count += 1
    rate.sleep()
