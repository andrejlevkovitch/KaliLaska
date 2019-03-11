// ShowEventSdl.cpp

#include "ShowEventSdl.hpp"
#include "SdlEvents.hpp"

namespace KaliLaska {
ShowEventSdl::ShowEventSdl(ShowAction action)
    : event_{} {
  event_.event = sdlAction(action);
}

ShowEventSdl::ShowEventSdl(const SDL_WindowEvent &event)
    : event_{event} {
}

ShowAction ShowEventSdl::action() const {
  return showAction(event_.event);
}
} // namespace KaliLaska
