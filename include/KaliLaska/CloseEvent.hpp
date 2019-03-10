// CloseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include <memory>

namespace KaliLaska {
class CloseEventImp;

class CloseEvent final : public Event {
public:
  CloseEvent();

  CloseEvent(std::unique_ptr<CloseEventImp> imp);

private:
  std::unique_ptr<CloseEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const CloseEvent &event);
} // namespace KaliLaska
