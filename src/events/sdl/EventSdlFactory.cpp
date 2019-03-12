// EventSdlFactory.cpp

#include "EventSdlFactory.hpp"
#include "CloseEventSdl.hpp"
#include "KaliLaska/Size.hpp"
#include "MouseFocusEventSdl.hpp"
#include "MouseMoveEventSdl.hpp"
#include "MousePressEventSdl.hpp"
#include "MouseReleaseEventSdl.hpp"
#include "MouseWheelEventSdl.hpp"
#include "ResizeEventSdl.hpp"
#include "ShowEventSdl.hpp"

namespace KaliLaska {
std::unique_ptr<CloseEventImp> EventSdlFactory::createCloseEventImp() {
  return std::make_unique<CloseEventSdl>();
}

std::unique_ptr<MousePressEventImp> EventSdlFactory::createMousePressImp(
    Mouse::Button button, Mouse::Click click, Point clickPos) {
  return std::make_unique<MousePressEventSdl>(button, click, clickPos);
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

std::unique_ptr<ShowEventImp>
EventSdlFactory::createShowEventImp(ShowAction action) {
  return std::make_unique<ShowEventSdl>(action);
}

std::unique_ptr<MouseFocusEventImp>
EventSdlFactory::createMouseFocusEvent(Mouse::Focus focus) {
  return std::make_unique<MouseFocusEventSdl>(focus);
}

std::unique_ptr<ResizeEventImp>
EventSdlFactory::createResizeEventImp(Size prev, Size next) {
  return std::make_unique<ResizeEventSdl>(prev, next);
}
} // namespace KaliLaska
