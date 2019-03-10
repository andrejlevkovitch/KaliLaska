// EventSdlFactory.cpp

#include "EventSdlFactory.hpp"
#include "CloseEventSdl.hpp"
#include "MouseMoveEventSdl.hpp"
#include "MousePressEventSdl.hpp"
#include "MouseReleaseEventSdl.hpp"
#include "MouseWheelEventSdl.hpp"

namespace KaliLaska {
std::unique_ptr<CloseEventImp> EventSdlFactory::createCloseEventImp() {
  return std::make_unique<CloseEventSdl>();
}

std::unique_ptr<MousePressEventImp>
EventSdlFactory::createMousePressImp(Mouse::Button button, Point clickPos) {
  return std::make_unique<MousePressEventSdl>(button, clickPos);
}

std::unique_ptr<MouseReleaseEventImp>
EventSdlFactory::createMouseReleaseImp(Mouse::Button button, Point clickPos) {
  return std::make_unique<MouseReleaseEventSdl>(button, clickPos);
}

std::unique_ptr<MouseMoveEventImp> EventSdlFactory::createMouseMoveEventImp(
    Mouse::Buttons buttons, Point curPos, Point prevPos) {
  return std::make_unique<MouseMoveEventSdl>(buttons, curPos, prevPos);
}

std::unique_ptr<MouseWheelEventImp>
EventSdlFactory::createMouseWheelEventImp(Mouse::Scale scale) {
  return std::make_unique<MouseWheelEventSdl>(scale);
}
} // namespace KaliLaska
