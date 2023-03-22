#ifndef KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_VISUAL_HPP_
#define KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_VISUAL_HPP_

// rviz
#include <rviz_default_plugins/displays/marker/markers/text_view_facing_marker.hpp>
#include "rviz_default_plugins/visibility_control.hpp"
#include "rviz_rendering/objects/arrow.hpp"
#include <rviz_rendering/objects/billboard_line.hpp>
#include <rviz_rendering/objects/movable_text.hpp>
#include "rviz_rendering/visibility_control.hpp"

// kindr ros
#include <kindr_msgs/msg/vector_at_position.hpp>

// Ogre
#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

namespace rviz_rendering
{
class Arrow;
class BillboardLine;
class MovableText;
} // rviz_rendering


namespace kindr_rviz_plugins
{

// Declare the visual class for this display.
//
// Each instance of VectorAtPositionVisual represents the visualization of a single
// sensor_msgs::VectorAtPosition message. Currently it just shows an arrow with
// the direction and magnitude of the acceleration vector, but could
// easily be expanded to include more of the message data.
class VectorAtPositionVisual
{
public:
  // Constructor. Creates the visual stuff and puts it into the
  // scene, but in an unconfigured state.
  VectorAtPositionVisual(Ogre::SceneManager * scene_manager, Ogre::SceneNode * parent_node);

  // Destructor. Removes the visual stuff from the scene.
  virtual ~VectorAtPositionVisual();

  // Configure the visual to show the data in the message.
  void setMessage(const kindr_msgs::msg::VectorAtPosition::ConstSharedPtr & msg);

  // Set the pose of the coordinate frame the message refers to.
  // These could be done inside setMessage(), but that would require
  // calls to FrameManager and error handling inside setMessage(),
  // which doesn't seem as clean. This way VectorAtPositionVisual is only
  // responsible for visualization.
  void setArrowPosition(const Ogre::Vector3 & position);
  void setArrowOrientation(const Ogre::Quaternion & orientation);

  // Set the scale of the visual, which are user-editable
  // parameters and therefore don't come from the VectorAtPosition message.
  void setScalingFactors(float lengthScalingFactor, float widthScalingFactor);

  // Enable or disable text rendering, which are user-editable
  // parameters and therefore don't come from the VectorAtPosition message.
  void setShowText(bool showText);

  // Set the color and alpha of the visual, which are user-editable
  // parameters and therefore don't come from the VectorAtPosition message.
  void setColor(const Ogre::ColourValue & color);

protected:
  // The object implementing the actual arrow shape
  std::shared_ptr<rviz_rendering::Arrow> arrow_;
  std::shared_ptr<rviz_rendering::Arrow> circleArrow_;
  std::shared_ptr<rviz_rendering::BillboardLine> circle_;

  // The object implementing the arrow description text
  std::shared_ptr<rviz_rendering::MovableText> text_;

  // Store the name
  std::string name_;

  // Store ogre vector and orientation
  Ogre::Vector3 vector_;

  // Store the scaling factor and the length of the vector, so that it can be scale afterwards
  float length_;
  float lengthScalingFactor_;
  float widthScalingFactor_;

  // Store show text
  bool showText_;
  bool showTorque_;

  // Store the arrow color
  Ogre::ColourValue color_;

  // A SceneNode whose pose is set to match the coordinate frame of
  // the VectorAtPosition message header.
  Ogre::SceneNode * scene_node_frame_;
  Ogre::SceneNode * scene_node_arrow_;
  Ogre::SceneNode * scene_node_circle_;
  Ogre::SceneNode * scene_node_text_;

  // The SceneManager, kept here only so the destructor can ask it to
  // destroy the ``frame_node_``.
  Ogre::SceneManager * scene_manager_;

  // Update the scaling of the arrow
  void updateScaling();

  // Update the color of the arrow
  void updateColor();

  // Update the text of the arrow
  void updateText();
};

} // kindr_rviz_plugins

#endif // KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_VISUAL_HPP_
