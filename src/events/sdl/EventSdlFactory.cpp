// EventSdlFactory.cpp

#include "EventSdlFactory.hpp"
#include "CloseEventSdl.hpp"
#include "KaliLaska/Size.hpp"
#include "KeyPressEventSdl.hpp"
#include "KeyReleaseEventSdl.hpp"
#include "KeyboardFocusEventSdl.hpp"
#include "MouseFocusEventSdl.hpp"
#include "MouseMoveEventSdl.hpp"
#include "MousePressEventSdl.hpp"
#include "MouseReleaseEventSdl.hpp"
#include "MouseWheelEventSdl.hpp"
#include "MoveEventSdl.hpp"
#include "ResizeEventSdl.hpp"
#include "ShowEventSdl.hpp"

namespace KaliLaska {
std::unique_ptr<CloseEventImp> EventSdlFactory::createCloseEventImp() const {
  return std::make_unique<CloseEventSdl>();
}

std::unique_ptr<MousePressEventImp> EventSdlFactory::createMousePressEventImp(
    Mouse::Button button, Mouse::Click click, Point clickPos) const {
  return std::make_unique<MousePressEventSdl>(button, click, clickPos);
}

std::unique_ptr<MouseReleaseEventImp>
EventSdlFactory::createMouseReleaseImp(Mouse::Button button,
                                       Point         clickPos) const {
  return std::make_unique<MouseReleaseEventSdl>(button, clickPos);
}

std::unique_ptr<MouseMoveEventImp> EventSdlFactory::createMouseMoveEventImp(
    Mouse::Buttons buttons, Point curPos, Point prevPos) const {
  return std::make_unique<MouseMoveEventSdl>(buttons, curPos, prevPos);
}

std::unique_ptr<MouseWheelEventImp>
EventSdlFactory::createMouseWheelEventImp(Mouse::Scale scale) const {
  return std::make_unique<MouseWheelEventSdl>(scale);
}

std::unique_ptr<ShowEventImp>
EventSdlFactory::createShowEventImp(ShowAction action) const {
  return std::make_unique<ShowEventSdl>(action);
}

std::unique_ptr<MouseFocusEventImp>
EventSdlFactory::createMouseFocusEventImp(Mouse::Focus focus) const {
  return std::make_unique<MouseFocusEventSdl>(focus);
}

std::unique_ptr<ResizeEventImp>
EventSdlFactory::createResizeEventImp(Size next) const {
  return std::make_unique<ResizeEventSdl>(next);
}

std::unique_ptr<KeyboardFocusEventImp>
EventSdlFactory::createKeyboardFocusEventImp(Keyboard::Focus focus) const {
  return std::make_unique<KeyboardFocusEventSdl>(focus);
}

std::unique_ptr<KeyPressEventImp> EventSdlFactory::createKeyPressEventImp(
    Keyboard::Key key, Keyboard::Modifyers modifyers, bool isRepeat) const {
  return std::make_unique<KeyPressEventSdl>(key, modifyers, isRepeat);
}

std::unique_ptr<KeyReleaseEventImp>
EventSdlFactory::createKeyReleaseEventImp(Keyboard::Key       key,
                                          Keyboard::Modifyers modifyers) const {
  return std::make_unique<KeyReleaseEventSdl>(key, modifyers);
}

std::unique_ptr<MoveEventImp>
EventSdlFactory::createMoveEventImp(Point cur) const {
  return std::make_unique<MoveEventSdl>(cur);
}
} // namespace KaliLaska
