// ResizeEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/ResizeEventImp.hpp"
#include <memory>

namespace KaliLaska {
class ResizeEvent : public Event {
public:
  ResizeEvent(std::unique_ptr<ResizeEventImp> imp);

  // TODO definition this

private:
  std::unique_ptr<ResizeEventImp> imp_;
};
} // namespace KaliLaska
