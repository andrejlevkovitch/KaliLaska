// ResizeEvent.cpp

#include "KaliLaska/ResizeEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"

namespace KaliLaska {
ResizeEvent::ResizeEvent(Size previousSize, Size newSize)
    : Event{Type::ResizeEvent}
    , imp_{Application::eventFactory()->createResizeEventImp(previousSize,
                                                             newSize)} {
}

ResizeEvent::ResizeEvent(std::unique_ptr<ResizeEventImp> imp)
    : Event{Type::ResizeEvent}
    , imp_{std::move(imp)} {
}

Size ResizeEvent::previousSize() const {
  return imp_->previousSize();
}

Size ResizeEvent::newSize() const {
  return imp_->newSize();
}

std::ostream &operator<<(std::ostream &stream, const ResizeEvent &event) {
  stream << "ResizeEvent: prevSize " << event.previousSize() << ", newSize "
         << event.newSize();
  return stream;
}
} // namespace KaliLaska
