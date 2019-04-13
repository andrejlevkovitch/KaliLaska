// NotifySceneState.hpp

#pragma once

#include "ViewState.hpp"

namespace KaliLaska {
class NotifySceneState final : public ViewState {
public:
  static ViewState *instance();

  Type type() const override;

  void mousePressEvent(GraphicsView *                   view,
                       std::unique_ptr<MousePressEvent> event) const override;
  void
       mouseReleaseEvent(GraphicsView *                     view,
                         std::unique_ptr<MouseReleaseEvent> event) const override;
  void mouseMoveEvent(GraphicsView *                  view,
                      std::unique_ptr<MouseMoveEvent> event) const override;

  void keyPressEvent(GraphicsView *                 view,
                     std::unique_ptr<KeyPressEvent> event) const override;
  void keyReleaseEvent(GraphicsView *                   view,
                       std::unique_ptr<KeyReleaseEvent> event) const override;

  void mouseFocusEvent(GraphicsView *                   view,
                       std::unique_ptr<MouseFocusEvent> event) const override;
};
} // namespace KaliLaska
