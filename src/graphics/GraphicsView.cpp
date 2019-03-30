// GraphicsView.cpp

#include "KaliLaska/GraphicsView.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/opengl.hpp"
#include "debug.hpp"
#include <GL/gl3w.h>

namespace KaliLaska {
GraphicsView::GraphicsView(std::string_view title,
                           const Point &    pos,
                           const Size &     size)
    : Window{title, pos, size}
    , scene_{}
    , sceneBox_{{0, 0}, {0, 0}} {
}

GraphicsScene *GraphicsView::scene() const {
  return scene_;
}

void GraphicsView::setScene(GraphicsScene *scene) {
  scene_ = scene;
}

void GraphicsView::update() {
}

void GraphicsView::setSceneBox(const Box &sceneBox) {
  // TODO change on matrix later
  sceneBox_ = sceneBox;
}

Box GraphicsView::sceneBox() const {
  return sceneBox_;
}

void GraphicsView::mousePressEvent(std::unique_ptr<MousePressEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::mouseWheelEvent(std::unique_ptr<MouseWheelEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::keyPressEvent(std::unique_ptr<KeyPressEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) {
  // TODO not implement
  UNUSED(event);
}

void GraphicsView::userEvent(std::unique_ptr<Event> event) {
  // TODO not implement
  UNUSED(event);
}
} // namespace KaliLaska
