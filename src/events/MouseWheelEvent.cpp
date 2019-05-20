// MouseWheelEvent.cpp

#include "KaliLaska/MouseWheelEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/MouseWheelEventImp.hpp"

namespace KaliLaska {
MouseWheelEvent::MouseWheelEvent(Mouse::Scale scale)
    : Event{Type::MouseWheelEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createMouseWheelEventImp(scale)} {
}

MouseWheelEvent::MouseWheelEvent(std::unique_ptr<MouseWheelEventImp> imp)
    : Event{Type::MouseWheelEvent}
    , imp_{std::move(imp)} {
}

MouseWheelEvent::~MouseWheelEvent() {
}

Point MouseWheelEvent::position() const {
  return imp_->position();
}

Mouse::Scale MouseWheelEvent::scale() const {
  return imp_->scale();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                    stream,
                         const KaliLaska::MouseWheelEvent &event) {
  using namespace KaliLaska;
  stream << "MouseWheelEvent: position " << event.position() << ", scale ";
  if (event.scale() != Mouse::Scale::Invalid) {
    stream << ((event.scale() == Mouse::Scale::ScaleDown) ? "Down" : "Up");
  } else {
    stream << "Invalid";
  }
  return stream;
}
