// GraphicsView.hpp

#pragma once

#include "Window.hpp"

namespace KaliLaska {
class GraphicsScene;

/**\brief display entity of GraphicsScen. One view can display only one scene
 */
class GraphicsView : public Window {
public:
  GraphicsView(const char *title, Point pos, Size size);
  ~GraphicsView() override = default;

  /**\warning not set ownershiep of scene
   */
  void setScene(GraphicsScene *scene);

private:
  GraphicsScene *scene_;
};
} // namespace KaliLaska
