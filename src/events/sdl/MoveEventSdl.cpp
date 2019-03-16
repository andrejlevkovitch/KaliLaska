// MoveEventSdl.cpp

#include "MoveEventSdl.hpp"
#include "debug.hpp"

namespace KaliLaska {
MoveEventSdl::MoveEventSdl(Point cur)
    : event_{} {
  event_.data1 = cur.x();
  event_.data2 = cur.y();
}

MoveEventSdl::MoveEventSdl(const SDL_WindowEvent &event)
    : event_{event} {
}

Point MoveEventSdl::currentPos() const {
  return {event_.data1, event_.data2};
}
} // namespace KaliLaska
