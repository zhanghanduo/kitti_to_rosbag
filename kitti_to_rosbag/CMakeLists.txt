cmake_minimum_required(VERSION 2.8.3)
project(kitti_to_rosbag)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

set(CMAKE_MACOSX_RPATH 0)
add_definitions(-std=c++11)

set(OpenCV_DIR $ENV{HOME}/softwares/opencv_3.4.1/opencv/release)
find_package(OpenCV 3.2 REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
)

#############
# LIBRARIES #
#############
cs_add_library(${PROJECT_NAME}
  src/kitti_parser.cpp
  src/kitti_ros_conversions.cpp
  src/kitti_common.cpp
)

############
# BINARIES #
############
cs_add_executable(kitti_live_node
  src/kitti_live_node.cpp
)
target_link_libraries(kitti_live_node ${PROJECT_NAME})

cs_add_executable(kitti_rosbag_converter
  src/kitti_rosbag_converter.cpp
)
target_link_libraries(kitti_rosbag_converter ${PROJECT_NAME})

cs_add_executable(tiny_disp_view
  src/tiny_disp_view.cpp
)
target_link_libraries(tiny_disp_view ${PROJECT_NAME} ${OpenCV_LIBS})

##########
# EXPORT #
##########
cs_install()
cs_export()
