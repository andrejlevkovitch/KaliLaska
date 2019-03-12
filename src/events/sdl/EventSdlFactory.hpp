// EventSdlFactory.hpp

#pragma once

#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
class EventSdlFactory final : public EventImpFactory {
public:
  std::unique_ptr<CloseEventImp> createCloseEventImp() override;

  std::unique_ptr<ShowEventImp> createShowEventImp(ShowAction action) override;

  std::unique_ptr<ResizeEventImp> createResizeEventImp(Size prev,
                                                       Size next) override;

  std::unique_ptr<MouseFocusEventImp>
  createMouseFocusEvent(Mouse::Focus focus) override;

  std::unique_ptr<MousePressEventImp> createMousePressImp(
      Mouse::Button button, Mouse::Click click, Point clickPos) override;

  std::unique_ptr<MouseReleaseEventImp>
  createMouseReleaseImp(Mouse::Button button, Point clickPos) override;

  std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) override;

  std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) override;
};
} // namespace KaliLaska
