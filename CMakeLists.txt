cmake_minimum_required(VERSION 2.8.3)
project(topic_throttle)

find_package(catkin REQUIRED COMPONENTS
  nodelet_topic_tools
  nodelet
  roscpp
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES topic_throttle
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(imu_sub src/imu_sub.cpp)
target_link_libraries(imu_sub ${catkin_LIBRARIES})

add_library(imu_nodelet_throttle src/imu_nodelet_throttle.cpp)
target_link_libraries(imu_nodelet_throttle ${catkin_LIBRARIES})

add_executable(imu_throttle src/imu_throttle.cpp)
target_link_libraries(imu_throttle ${catkin_LIBRARIES})
