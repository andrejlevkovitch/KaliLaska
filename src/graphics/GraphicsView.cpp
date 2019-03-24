// GraphicsView.cpp

#include "KaliLaska/GraphicsView.hpp"
#include "debug.hpp"

namespace KaliLaska {
GraphicsView::GraphicsView(std::string_view title,
                           const Point &    pos,
                           const Size &     size)
    : Window{title, pos, size}
    , scene_{} {
}

GraphicsScene *GraphicsView::scene() const {
  return scene_;
}

void GraphicsView::setScene(GraphicsScene *scene) {
  scene_ = scene;
}

void GraphicsView::setSceneRect(const Rect &sceneRect) {
  // TODO not implement
  UNUSED(sceneRect);
}

void GraphicsView::resizeEvent(std::unique_ptr<ResizeEvent> event) {
  // TODO not implement
  UNUSED(event);
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
