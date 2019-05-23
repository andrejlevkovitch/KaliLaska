// NotifySceneState.cpp

#include "NotifySceneState.hpp"
#include "KaliLaska/AbstractGraphicsView.hpp"
#include "KaliLaska/GraphicsScene.hpp"
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

namespace KaliLaska {
static NotifySceneState instanceI;

ViewState *NotifySceneState::instance() {
  return &instanceI;
}

ViewState::Type NotifySceneState::type() const {
  return Type::NotifySceneState;
}

void NotifySceneState::mousePressEvent(
    AbstractGraphicsView *view, std::unique_ptr<MousePressEvent> event) const {
  if (view->scene() && event) {
    auto sceneEvent =
        std::make_unique<SceneMousePressEvent>(std::move(event), view->matrix_);
    view->scene()->mousePressEvent(sceneEvent.get());
    if (!sceneEvent->accepted() &&
        sceneEvent->buttons() & Mouse::Button::Left) {
      view->changeState(MoveSceneState::instance());
    }
  }
}

void NotifySceneState::mouseReleaseEvent(
    AbstractGraphicsView *             view,
    std::unique_ptr<MouseReleaseEvent> event) const {
  if (view->scene() && event) {
    auto sceneEvent = std::make_unique<SceneMouseReleaseEvent>(std::move(event),
                                                               view->matrix_);
    view->scene()->mouseReleaseEvent(sceneEvent.get());
  }
}

void NotifySceneState::mouseMoveEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseMoveEvent> event) const {
  if (view->scene() && event) {
    auto sceneEvent =
        std::make_unique<SceneMouseMoveEvent>(std::move(event), view->matrix_);
    view->scene()->mouseMoveEvent(sceneEvent.get());
  }
}

void NotifySceneState::keyPressEvent(
    AbstractGraphicsView *view, std::unique_ptr<KeyPressEvent> event) const {
  if (view->scene() && event) {
    view->scene()->keyPressEvent(event.get());
  }
}

void NotifySceneState::keyReleaseEvent(
    AbstractGraphicsView *view, std::unique_ptr<KeyReleaseEvent> event) const {
  if (view->scene() && event) {
    view->scene()->keyReleaseEvent(event.get());
  }
}

void NotifySceneState::mouseFocusEvent(
    AbstractGraphicsView *view, std::unique_ptr<MouseFocusEvent> event) const {
  if (view->scene() && event) {
    view->scene()->mouseFocusEvent(event.get());
  }
}
} // namespace KaliLaska
