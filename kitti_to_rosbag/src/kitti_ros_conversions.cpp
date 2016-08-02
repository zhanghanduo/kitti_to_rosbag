#include <cv_bridge/cv_bridge.h>
#include <minkindr_conversions/kindr_msg.h>
#include <minkindr_conversions/kindr_tf.h>

#include "kitti_to_rosbag/kitti_ros_conversions.h"

namespace kitti {

void calibrationToRos(uint64_t cam_id, const CameraCalibration& cam,
                      sensor_msgs::CameraInfo* cam_msg) {




}

void stereoCalibrationToRos(uint64_t left_cam_id, uint64_t right_cam_id,
                            const CameraCalibration& left_cam,
                            const CameraCalibration& right_cam,
                            sensor_msgs::CameraInfo* left_cam_msg,
                            sensor_msgs::CameraInfo* right_cam_msg) {
  // Fill in the basics for each camera.
  calibrationToRos(left_cam_id, left_cam, left_cam_msg);
  calibrationToRos(right_cam_id, right_cam, right_cam_msg);

  // Since all transforms are given relative to cam0, need to remove the cam0
  // transform from both to get the relative one between the two (cam0 to cam0
  // is ostensibly identity anyway).
  Transformation T_left_cam0 = left_cam.T_cam0_cam.inverse();
  Transformation T_left_right = T_left_cam0 * right_cam.T_cam0_cam;





}

void imageToRos(const cv::Mat& image, sensor_msgs::Image* image_msg) {
  cv_bridge::CvImage image_cv_bridge;
  image_cv_bridge.image = image;
  *image_msg = *image_cv_bridge.toImageMsg();
}

void poseToRos(const Transformation& transform,
               geometry_msgs::PoseStamped* pose_msg) {
  tf::poseKindrToMsg(transform, &pose_msg->pose);
}

void transformToRos(const Transformation& transform,
                    tf::Transform* tf_transform) {

  tf::transformKindrToTF(transform, tf_transform);
}

void timestampToRos(uint64_t timestamp_ns, ros::Time* time) {
  time->fromNSec(timestamp_ns);
}

}  // namespace kitti
