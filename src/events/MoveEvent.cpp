// MoveEvent.cpp

#include "KaliLaska/MoveEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
MoveEvent::MoveEvent(Point curPos)
    : Event{Type::MoveEvent}
    , imp_{Application::eventFactory()->createMoveEventImp(curPos)} {
}

MoveEvent::MoveEvent(std::unique_ptr<MoveEventImp> imp)
    : Event{Type::MoveEvent}
    , imp_{std::move(imp)} {
}

Point MoveEvent::currentPos() const {
  return imp_->currentPos();
}

std::ostream &operator<<(std::ostream &stream, const MoveEvent &event) {
  stream << "MoveEvent: curPos " << event.currentPos();
  return stream;
}
} // namespace KaliLaska
