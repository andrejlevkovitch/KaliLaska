// UnModificableState.cpp

#include "UnModificableState.hpp"
#include "KaliLaska/AbstractGraphicsView.hpp"
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
    AbstractGraphicsView *view, std::unique_ptr<MousePressEvent> event) const {
  if (event->buttons() & Mouse::Button::Left &&
      view->properties_ & AbstractGraphicsView::Property::Movable) {
    view->changeState(MoveSceneState::instance());
  }
}

void UnModificableState::mouseReleaseEvent(
    AbstractGraphicsView *             view,
    std::unique_ptr<MouseReleaseEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::mouseMoveEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseMoveEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::keyPressEvent(
    AbstractGraphicsView *view, std::unique_ptr<KeyPressEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::keyReleaseEvent(
    AbstractGraphicsView *view, std::unique_ptr<KeyReleaseEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}

void UnModificableState::mouseFocusEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseFocusEvent> event) const {
  UNUSED(view);
  UNUSED(event);
}
} // namespace KaliLaska
