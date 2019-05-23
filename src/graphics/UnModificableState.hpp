// UnModificableState.hpp

#pragma once

#include "ViewState.hpp"

namespace KaliLaska {
class UnModificableState final : public ViewState {
public:
  static ViewState *instance();

  Type type() const override;

  void mousePressEvent(AbstractGraphicsView *           view,
                       std::unique_ptr<MousePressEvent> event) const override;
  void
       mouseReleaseEvent(AbstractGraphicsView *             view,
                         std::unique_ptr<MouseReleaseEvent> event) const override;
  void mouseMoveEvent(AbstractGraphicsView *          view,
                      std::unique_ptr<MouseMoveEvent> event) const override;

  void keyPressEvent(AbstractGraphicsView *         view,
                     std::unique_ptr<KeyPressEvent> event) const override;
  void keyReleaseEvent(AbstractGraphicsView *           view,
                       std::unique_ptr<KeyReleaseEvent> event) const override;

  void mouseFocusEvent(AbstractGraphicsView *           view,
                       std::unique_ptr<MouseFocusEvent> event) const override;
};
} // namespace KaliLaska
