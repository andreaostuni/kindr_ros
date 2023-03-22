#ifndef KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_DISPLAY_HPP_
#define KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_DISPLAY_HPP_

#ifndef Q_MOC_RUN
// boost
#include <boost/circular_buffer.hpp>

// rviz
#include "rviz_common/message_filter_display.hpp"
#include <rviz_common/properties/color_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/int_property.hpp>

// kindr ros
#include <kindr_msgs/msg/vector_at_position.hpp>

// ogre
#include <OgreColourValue.h>
#endif

// ogre
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

// tf
#include <tf2_ros/transform_listener.h>

// rviz
#include <rviz_common/visualization_manager.hpp>
#include <rviz_common/properties/color_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/int_property.hpp>
#include <rviz_common/frame_manager_iface.hpp>


namespace Ogre
{
class SceneNode;
} // Ogre

// namespace rviz_common
// {
// class BoolProperty;
// class ColorProperty;
// class FloatProperty;
// class IntProperty;
// class DisplayContext;
// } // rviz


// All the source in this plugin is in its own namespace. This is not
// required but is good practice.
namespace kindr_rviz_plugins
{

class VectorAtPositionVisual;

// Here we declare our new subclass of rviz::Display. Every display
// which can be listed in the "Displays" panel is a subclass of
// rviz::Display.
//
// VectorAtPositionDisplay will show a 3D arrow showing the direction and magnitude
// of the IMU acceleration vector. The base of the arrow will be at
// the frame listed in the header of the VectorAtPosition message, and the
// direction of the arrow will be relative to the orientation of that
// frame. It will also optionally show a history of recent
// acceleration vectors, which will be stored in a circular buffer.
//
// The VectorAtPositionDisplay class itself just implements the circular buffer,
// editable parameters, and Display subclass machinery. The visuals
// themselves are represented by a separate class, VectorAtPositionVisual. The
// idiom for the visuals is that when the objects exist, they appear
// in the scene, and when they are deleted, they disappear.
class VectorAtPositionDisplay : public rviz_common::MessageFilterDisplay<kindr_msgs::msg::VectorAtPosition>
{
  Q_OBJECT

public:
  // TODO(botteroa-si): Constructor for testing, remove once ros_nodes can be mocked and call
  // initialize instead
  // VectorAtPositionDisplay(
  //   rviz_common::DisplayContext * display_context,
  //   Ogre::SceneNode * scene_node);
  VectorAtPositionDisplay();
  virtual ~VectorAtPositionDisplay();

  // Overrides of protected virtual functions from Display. As much
  // as possible, when Displays are not enabled, they should not be
  // subscribed to incoming data and should not show anything in the
  // 3D view. These functions are where these connections are made
  // and broken.

protected:
  virtual void onInitialize();

  // A helper to clear this display back to the initial state.
  virtual void reset();

Q_SIGNALS:
  void updateVectorAtPositionSignal();

  // These Qt slots get connected to signals indicating changes in the user-editable properties.

private Q_SLOTS:
  void updateScale();
  void updateShowText();
  void updateColorAndAlpha();
  void updateHistoryLength();

  void updateVectorAtPosition();

  // Function to handle an incoming ROS message.

private:
  void processMessage(kindr_msgs::msg::VectorAtPosition::ConstSharedPtr msg);

  // Storage for the list of visuals. It is a circular buffer where
  // data gets popped from the front (oldest) and pushed to the back (newest)
  boost::circular_buffer<std::shared_ptr<VectorAtPositionVisual>> visuals_;

  // User-editable property variables.
  rviz_common::properties::FloatProperty * length_scale_property_;
  rviz_common::properties::FloatProperty * width_scale_property_;
  rviz_common::properties::BoolProperty * show_text_property_;
  rviz_common::properties::ColorProperty * color_property_;
  rviz_common::properties::FloatProperty * alpha_property_;
  rviz_common::properties::IntProperty * history_length_property_;

  // Storage of user editable values
  float lengthScale_;
  float widthScale_;
  bool showText_;
  Ogre::ColourValue color_;
  float alpha_;

  kindr_msgs::msg::VectorAtPosition::ConstSharedPtr current_vector_at_position_;
};

} // kindr_rviz_plugins

#endif // KINDR_RVIZ_PLUGINS_VECTOR_AT_POSITION_DISPLAY_HPP_
