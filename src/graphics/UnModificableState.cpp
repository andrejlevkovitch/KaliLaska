// UnModificableState.cpp

#include "UnModificableState.hpp"
#include "KaliLaska/GraphicsView.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "MoveSceneState.hpp"
#include "debug.hpp"

namespace KaliLaska {
static UnModificableState instanceI;

ViewState *UnModificableState::instance() {
  return &instanceI;
}

ViewState::Type UnModificableState::type() const {
  return Type::UnModificableState;
}

void UnModificableState::mousePressEvent(
    GraphicsView *view, std::unique_ptr<MousePressEvent> event) const {
  if (event->buttons() & Mouse::Button::Left &&
      view->properties_ & GraphicsView::Property::Movable) {
    view->changeState(MoveSceneState::instance());
  }
}

void UnModificableState::mouseReleaseEvent(
    GraphicsView *view, std::unique_ptr<MouseReleaseEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::mouseMoveEvent(
    GraphicsView *view, std::unique_ptr<MouseMoveEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::keyPressEvent(
    GraphicsView *view, std::unique_ptr<KeyPressEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::keyReleaseEvent(
    GraphicsView *view, std::unique_ptr<KeyReleaseEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::mouseFocusEvent(
    GraphicsView *view, std::unique_ptr<MouseFocusEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}
} // namespace KaliLaska
