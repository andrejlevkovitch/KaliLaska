// EventNotifyer.cpp

#include "KaliLaska/EventNotifyer.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/CloseEventImp.hpp"
#include "KaliLaska/Event.hpp"
#include "KaliLaska/MouseMoveEvent.hpp"
#include "KaliLaska/MouseMoveEventImp.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/MousePressEventImp.hpp"
#include "KaliLaska/MouseReleaseEvent.hpp"
#include "KaliLaska/MouseReleaseEventImp.hpp"
#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/MouseWheelEventImp.hpp"
#include "KaliLaska/Window.hpp"

namespace KaliLaska {
// custom unique cast
template <typename R, typename T>
std::unique_ptr<R> uniqueCast(T &t) {
  auto ptr = t.release();
  return std::unique_ptr<R>(reinterpret_cast<R *>(ptr));
}

void EventNotifyer::notify(Window *window, std::unique_ptr<Event> event) {
  if (window && event) {
    switch (event->type()) {
    case Event::Type::CloseEvent:
      window->closeEvent(uniqueCast<CloseEvent>(event));
      break;
    case Event::Type::MouseMoveEvent:
      window->mouseMoveEvent(uniqueCast<MouseMoveEvent>(event));
      break;
    case Event::Type::MousePressEvent:
      window->mousePressEvent(uniqueCast<MousePressEvent>(event));
      break;
    case Event::Type::MouseReleaseEvent:
      window->mouseReleaseEvent(uniqueCast<MouseReleaseEvent>(event));
      break;
    case Event::Type::MouseWheelEvent:
      window->mouseWheelEvent(uniqueCast<MouseWheelEvent>(event));
      break;
    default:
      break;
    }
  }
}
} // namespace KaliLaska
