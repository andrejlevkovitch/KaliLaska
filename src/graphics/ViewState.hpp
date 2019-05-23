// ViewState.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class AbstractGraphicsView;

class MouseMoveEvent;
class MousePressEvent;
class MouseReleaseEvent;
class MouseFocusEvent;

class KeyPressEvent;
class KeyReleaseEvent;

class ViewState {
public:
  enum Type { UnModificableState, NotifySceneState, MoveSceneState };

  virtual ~ViewState() = default;

  virtual Type type() const = 0;

  virtual void
  mousePressEvent(AbstractGraphicsView *           view,
                  std::unique_ptr<MousePressEvent> event) const = 0;
  virtual void
               mouseReleaseEvent(AbstractGraphicsView *             view,
                                 std::unique_ptr<MouseReleaseEvent> event) const = 0;
  virtual void mouseMoveEvent(AbstractGraphicsView *          view,
                              std::unique_ptr<MouseMoveEvent> event) const = 0;

  virtual void keyPressEvent(AbstractGraphicsView *         view,
                             std::unique_ptr<KeyPressEvent> event) const = 0;
  virtual void
  keyReleaseEvent(AbstractGraphicsView *           view,
                  std::unique_ptr<KeyReleaseEvent> event) const = 0;

  virtual void
  mouseFocusEvent(AbstractGraphicsView *           view,
                  std::unique_ptr<MouseFocusEvent> event) const = 0;
};
} // namespace KaliLaska
