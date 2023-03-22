#ifndef MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_DISPLAY_HPP
#define MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_DISPLAY_HPP

#ifndef Q_MOC_RUN
#include <vector>

#include <boost/circular_buffer.hpp>

#include <rviz_common/message_filter_display.hpp>
#include <trajectory_msgs/msg/multi_dof_joint_trajectory.hpp>
#endif

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include <tf2_ros/transform_listener.h>

#include <rviz_common/visualization_manager.hpp>
#include <rviz_common/properties/bool_property.hpp>
#include <rviz_common/properties/int_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/color_property.hpp>
#include <rviz_common/properties/parse_color.hpp>
#include <rviz_common/frame_manager_iface.hpp>

#include "multi_dof_joint_trajectory_rviz_plugins/MultiDOFJointTrajectoryPointConnectionVisual.hpp"
#include "multi_dof_joint_trajectory_rviz_plugins/MultiDOFJointTrajectoryPointVisual.hpp"


namespace multi_dof_joint_trajectory_rviz_plugins
{

class MultiDOFJointTrajectoryDisplay : public rviz_common::MessageFilterDisplay<trajectory_msgs::msg::MultiDOFJointTrajectory>
{
  Q_OBJECT

public:
  MultiDOFJointTrajectoryDisplay();
  virtual ~MultiDOFJointTrajectoryDisplay();

protected:
  virtual void onInitialize();
  virtual void reset();

Q_SIGNALS:
  void updateTrajectorySignal();

private Q_SLOTS:
  void setShowConnection();
  void setShowTransformRotation();
  void setShowVelocityLinear();
  void setShowVelocityAngular();
  void setShowAccelerationLinear();
  void setShowAccelerationAngular();

  void setSizeTransformRotation();
  void setDiameterArrows();
  void setScaleVelocityLinear();
  void setScaleVelocityAngular();
  void setScaleAccelerationLinear();
  void setScaleAccelerationAngular();

  void setAlpha();
  void setColorConnection();
  void setColorVelocityLinear();
  void setColorVelocityAngular();
  void setColorAccelerationLinear();
  void setColorAccelerationAngular();

  void setFontSize();
  void setShowText();

  void setHistoryLength();

  void updateTrajectory();

private:
  void processMessage(const trajectory_msgs::msg::MultiDOFJointTrajectory::ConstSharedPtr msg);

  void updateShowConnection();
  void updateShowTransformRotation();
  void updateShowVelocityLinear();
  void updateShowVelocityAngular();
  void updateShowAccelerationLinear();
  void updateShowAccelerationAngular();

  void updateSizeTransformRotation();
  void updateDiameterArrows();
  void updateScaleVelocityLinear();
  void updateScaleVelocityAngular();
  void updateScaleAccelerationLinear();
  void updateScaleAccelerationAngular();

  void updateColorConnection();
  void updateAlphaTransformRotation();
  void updateColorVelocityLinear();
  void updateColorVelocityAngular();
  void updateColorAccelerationLinear();
  void updateColorAccelerationAngular();

  void updateFontSize();
  void updateShowText();

  boost::circular_buffer<std::vector<std::shared_ptr<MultiDOFJointTrajectoryPointVisual>>>
  visuals_points_;
  boost::circular_buffer<std::vector<std::shared_ptr<MultiDOFJointTrajectoryPointConnectionVisual>>>
  visuals_connections_;

  rviz_common::properties::BoolProperty * property_show_connection_;
  rviz_common::properties::BoolProperty * property_show_transform_rotation_;
  rviz_common::properties::BoolProperty * property_show_velocity_linear_;
  rviz_common::properties::BoolProperty * property_show_velocity_angular_;
  rviz_common::properties::BoolProperty * property_show_acceleration_linear_;
  rviz_common::properties::BoolProperty * property_show_acceleration_angular_;

  rviz_common::properties::FloatProperty * property_size_transform_rotation_;
  rviz_common::properties::FloatProperty * property_diameter_arrows_;
  rviz_common::properties::FloatProperty * property_scale_velocity_linear_;
  rviz_common::properties::FloatProperty * property_scale_velocity_angular_;
  rviz_common::properties::FloatProperty * property_scale_acceleration_linear_;
  rviz_common::properties::FloatProperty * property_scale_acceleration_angular_;

  rviz_common::properties::ColorProperty * property_color_connection_;
  rviz_common::properties::ColorProperty * property_color_velocity_linear_;
  rviz_common::properties::ColorProperty * property_color_velocity_angular_;
  rviz_common::properties::ColorProperty * property_color_acceleration_linear_;
  rviz_common::properties::ColorProperty * property_color_acceleration_angular_;

  rviz_common::properties::FloatProperty * property_alpha_;

  rviz_common::properties::FloatProperty * property_font_size_;
  rviz_common::properties::BoolProperty * property_show_text_;

  rviz_common::properties::IntProperty * property_history_length_;

  bool show_connection_;
  bool show_transform_rotation_;
  bool show_velocity_linear_;
  bool show_velocity_angular_;
  bool show_acceleration_linear_;
  bool show_acceleration_angular_;

  float size_transform_rotation_;
  float diameter_arrows_;
  float scale_velocity_linear_;
  float scale_velocity_angular_;
  float scale_acceleration_linear_;
  float scale_acceleration_angular_;

  float alpha_;
  Ogre::ColourValue color_connection_;
  Ogre::ColourValue color_velocity_linear_;
  Ogre::ColourValue color_velocity_angular_;
  Ogre::ColourValue color_acceleration_linear_;
  Ogre::ColourValue color_acceleration_angular_;

  float font_size_;
  bool show_text_;

  trajectory_msgs::msg::MultiDOFJointTrajectory::ConstSharedPtr current_trajectory_;
};

} // multi_dof_joint_trajectory_rviz_plugins

#endif // MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_DISPLAY_HPP
