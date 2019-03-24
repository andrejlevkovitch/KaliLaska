// GraphicsItem.cpp

#include "KaliLaska/GraphicsItem.hpp"
#include "debug.hpp"

namespace KaliLaska {
GraphicsItem::GraphicsItem() {
}

void GraphicsItem::mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mousePressEvent(
    std::unique_ptr<SceneMousePressEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::mouseReleaseEvent(
    std::unique_ptr<SceneMouseReleaseEvent> event) {
  // TODO implement
  UNUSED(event);
}

void GraphicsItem::userEvent(std::unique_ptr<Event> event) {
  // TODO implement
  UNUSED(event);
}

} // namespace KaliLaska
