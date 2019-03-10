// CloseEventSdl.cpp

#include "CloseEventSdl.hpp"

namespace KaliLaska {
CloseEventSdl::CloseEventSdl()
    : event_{} {
}

CloseEventSdl::CloseEventSdl(const SDL_WindowEvent &event)
    : event_{event} {
}
} // namespace KaliLaska
