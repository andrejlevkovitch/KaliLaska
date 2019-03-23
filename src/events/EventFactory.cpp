// EventFactory.cpp

#include "EventFactory.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/KeyboardFocusEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/MoveEvent.hpp"
#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/ShowEvent.hpp"
#include "imp/CloseEventImp.hpp"
#include "imp/KeyPressEventImp.hpp"
#include "imp/KeyReleaseEventImp.hpp"
#include "imp/KeyboardFocusEventImp.hpp"
#include "imp/MouseFocusEventImp.hpp"
#include "imp/MouseMoveEventImp.hpp"
#include "imp/MousePressEventImp.hpp"
#include "imp/MouseReleaseEventImp.hpp"
#include "imp/MouseWheelEventImp.hpp"
#include "imp/MoveEventImp.hpp"
#include "imp/ResizeEventImp.hpp"
#include "imp/ShowEventImp.hpp"

namespace KaliLaska {
std::unique_ptr<CloseEvent>
EventFactory::event(std::unique_ptr<CloseEventImp> imp) {
  return std::unique_ptr<CloseEvent>{new CloseEvent{std::move(imp)}};
}

std::unique_ptr<ShowEvent>
EventFactory::event(std::unique_ptr<ShowEventImp> imp) {
  return std::unique_ptr<ShowEvent>{new ShowEvent{std::move(imp)}};
}

std::unique_ptr<ResizeEvent>
EventFactory::event(std::unique_ptr<ResizeEventImp> imp) {
  return std::unique_ptr<ResizeEvent>{new ResizeEvent{std::move(imp)}};
}

std::unique_ptr<MoveEvent>
EventFactory::event(std::unique_ptr<MoveEventImp> imp) {
  return std::unique_ptr<MoveEvent>{new MoveEvent{std::move(imp)}};
}

std::unique_ptr<MouseFocusEvent>
EventFactory::event(std::unique_ptr<MouseFocusEventImp> imp) {
  return std::unique_ptr<MouseFocusEvent>{new MouseFocusEvent{std::move(imp)}};
}

std::unique_ptr<MouseMoveEvent>
EventFactory::event(std::unique_ptr<MouseMoveEventImp> imp) {
  return std::unique_ptr<MouseMoveEvent>{new MouseMoveEvent{std::move(imp)}};
}

std::unique_ptr<MousePressEvent>
EventFactory::event(std::unique_ptr<MousePressEventImp> imp) {
  return std::unique_ptr<MousePressEvent>{new MousePressEvent{std::move(imp)}};
}

std::unique_ptr<MouseReleaseEvent>
EventFactory::event(std::unique_ptr<MouseReleaseEventImp> imp) {
  return std::unique_ptr<MouseReleaseEvent>{
      new MouseReleaseEvent{std::move(imp)}};
}

std::unique_ptr<MouseWheelEvent>
EventFactory::event(std::unique_ptr<MouseWheelEventImp> imp) {
  return std::unique_ptr<MouseWheelEvent>{new MouseWheelEvent{std::move(imp)}};
}

std::unique_ptr<KeyboardFocusEvent>
EventFactory::event(std::unique_ptr<KeyboardFocusEventImp> imp) {
  return std::unique_ptr<KeyboardFocusEvent>{
      new KeyboardFocusEvent{std::move(imp)}};
}

std::unique_ptr<KeyPressEvent>
EventFactory::event(std::unique_ptr<KeyPressEventImp> imp) {
  return std::unique_ptr<KeyPressEvent>{new KeyPressEvent{std::move(imp)}};
}

std::unique_ptr<KeyReleaseEvent>
EventFactory::event(std::unique_ptr<KeyReleaseEventImp> imp) {
  return std::unique_ptr<KeyReleaseEvent>{new KeyReleaseEvent{std::move(imp)}};
}
} // namespace KaliLaska
