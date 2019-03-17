// EventSdlFactory.hpp

#pragma once

#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
class EventSdlFactory final : public EventImpFactory {
public:
  std::unique_ptr<CloseEventImp> createCloseEventImp() const override;

  std::unique_ptr<ShowEventImp>
  createShowEventImp(ShowAction action) const override;

  std::unique_ptr<ResizeEventImp>
  createResizeEventImp(Size next) const override;

  std::unique_ptr<MoveEventImp> createMoveEventImp(Point cur) const override;

  //----------------------------------------------------------------------------

  std::unique_ptr<MouseFocusEventImp>
  createMouseFocusEventImp(Mouse::Focus focus) const override;

  std::unique_ptr<MousePressEventImp> createMousePressEventImp(
      Mouse::Button button, Mouse::Click click, Point clickPos) const override;

  std::unique_ptr<MouseReleaseEventImp>
  createMouseReleaseImp(Mouse::Button button, Point clickPos) const override;

  std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) const override;

  std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) const override;

  //----------------------------------------------------------------------------

  std::unique_ptr<KeyboardFocusEventImp>
  createKeyboardFocusEventImp(Keyboard::Focus focus) const override;

  std::unique_ptr<KeyPressEventImp>
  createKeyPressEventImp(Keyboard::Key       key,
                         Keyboard::Modifyers modifyers,
                         bool                isRepeat) const override;

  std::unique_ptr<KeyReleaseEventImp>
  createKeyReleaseEventImp(Keyboard::Key       key,
                           Keyboard::Modifyers modifyers) const override;
};
} // namespace KaliLaska
