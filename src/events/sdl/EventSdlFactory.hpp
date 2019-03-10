// EventSdlFactory.hpp

#pragma once

#include "KaliLaska/EventImpFactory.hpp"

namespace KaliLaska {
class EventSdlFactory final : public EventImpFactory {
public:
  std::unique_ptr<CloseEventImp> createCloseEventImp() override;
  std::unique_ptr<MousePressEventImp>
  createMousePressImp(Mouse::Button button, Point clickPos) override;
  std::unique_ptr<MouseReleaseEventImp>
                                     createMouseReleaseImp(Mouse::Button button, Point clickPos) override;
  std::unique_ptr<MouseMoveEventImp> createMouseMoveEventImp(
      Mouse::Buttons buttons, Point curPos, Point prevPos) override;
  std::unique_ptr<MouseWheelEventImp>
  createMouseWheelEventImp(Mouse::Scale scale) override;
};
} // namespace KaliLaska
