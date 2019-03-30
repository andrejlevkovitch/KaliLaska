// GraphicsView.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Window.hpp"

namespace KaliLaska {
class GraphicsScene;

/**\brief display entity of GraphicsScen. One view can display only one scene
 */
class GraphicsView : public Window {
public:
  GraphicsView(std::string_view title, const Point &pos, const Size &size);
  ~GraphicsView() override = default;

  /**\warning not set ownershiep of scene
   */
  virtual void   setScene(GraphicsScene *scene);
  GraphicsScene *scene() const;

  void setSceneBox(const Box &sceneBox);
  Box  sceneBox() const;

  void update() override;

protected:
  void resizeEvent(std::unique_ptr<ResizeEvent> event) override;

  void mousePressEvent(std::unique_ptr<MousePressEvent> event) override;
  void mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) override;
  void mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) override;
  void mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event) override;

  void keyPressEvent(std::unique_ptr<KeyPressEvent> event) override;
  void keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) override;

  void userEvent(std::unique_ptr<Event> event) override;

private:
  GraphicsScene *scene_;

  /**\brief this is scene postion, which in the top left corner of view. By
   * default {0, 0}
   */
  // TODO this is need change on matrix
  Box sceneBox_;
};
} // namespace KaliLaska
