#ifndef MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_POINT_CONNECTION_VISUAL_HPP_
#define MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_POINT_CONNECTION_VISUAL_HPP_
// Ogre
#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

// Rviz
#include <rviz_rendering/objects/line.hpp>
#include <rviz_rendering/objects/movable_text.hpp>
#include "rviz_rendering/visibility_control.hpp"
#include <rviz_default_plugins/displays/marker/markers/text_view_facing_marker.hpp>

// ROS msgs
#include <trajectory_msgs/msg/multi_dof_joint_trajectory_point.hpp>


namespace multi_dof_joint_trajectory_rviz_plugins
{

class MultiDOFJointTrajectoryPointConnectionVisual
{
public:
  MultiDOFJointTrajectoryPointConnectionVisual(
    Ogre::SceneManager * scene_manager,
    Ogre::SceneNode * parent_node,
    const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & from,
    const trajectory_msgs::msg::MultiDOFJointTrajectoryPoint & to,
    float show_connection,
    const Ogre::ColourValue & color);
  virtual ~MultiDOFJointTrajectoryPointConnectionVisual();

  void setShowConnection(bool visible);
  void setColor(const Ogre::ColourValue & color);

private:
  void updateShowConnection();
  void updateColor();

  Ogre::SceneManager * scene_manager_;

  Ogre::SceneNode * scene_node_;

  std::vector<std::shared_ptr<rviz_rendering::Line>> lines_;

  float show_connection_;
  Ogre::ColourValue color_;
};

} // multi_dof_joint_trajectory_rviz_plugins

#endif // MULTI_DOF_JOINT_TRAJECTORY_RVIZ_PLUGINS_MULTI_DOF_JOINT_TRAJECTORY_POINT_CONNECTION_VISUAL_HPP_
