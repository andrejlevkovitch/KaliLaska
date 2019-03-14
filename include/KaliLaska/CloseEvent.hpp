// CloseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/CloseEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT CloseEvent final : public Event {
public:
  CloseEvent();
  CloseEvent(std::unique_ptr<CloseEventImp> imp);

private:
  std::unique_ptr<CloseEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const CloseEvent &event);
} // namespace KaliLaska
