// ResizeEvent.cpp

#include "KaliLaska/ResizeEvent.hpp"

namespace KaliLaska {
ResizeEvent::ResizeEvent(std::unique_ptr<ResizeEventImp> imp)
    : Event{Type::ResizeEvent}
    , imp_{std::move(imp)} {
}
} // namespace KaliLaska
