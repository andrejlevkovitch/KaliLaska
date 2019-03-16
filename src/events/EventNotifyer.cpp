// EventNotifyer.cpp

#include "KaliLaska/EventNotifyer.hpp"
#include "KaliLaska/CloseEvent.hpp"
#include "KaliLaska/Event.hpp"
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
    case Event::Type::ShowEvent:
      window->showEvent(uniqueCast<ShowEvent>(event));
      break;
    case Event::Type::ResizeEvent:
      window->resizeEvent(uniqueCast<ResizeEvent>(event));
      break;
    case Event::Type::MoveEvent:
      window->moveEvent(uniqueCast<MoveEvent>(event));
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
    case Event::Type::MouseFocusEvent:
      window->mouseFocusEvent(uniqueCast<MouseFocusEvent>(event));
      break;
    case Event::Type::KeyboardFocusEvent:
      window->keyboardFocusEvent(uniqueCast<KeyboardFocusEvent>(event));
      break;
    case Event::Type::KeyPressEvent:
      window->keyPressEvent(uniqueCast<KeyPressEvent>(event));
      break;
    case Event::Type::KeyReleaseEvent:
      window->keyReleaseEvent(uniqueCast<KeyReleaseEvent>(event));
      break;
    default:
      window->userEvent(std::move(event));
      break;
    }
  }
}
} // namespace KaliLaska
