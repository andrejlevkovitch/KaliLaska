// ShowEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/ShowEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
/**\brief represent window events AFTER some action
 */
class KALILASKA_EXPORT ShowEvent final : public Event {
public:
  explicit ShowEvent(ShowAction action);
  explicit ShowEvent(std::unique_ptr<ShowEventImp> imp);

  ShowAction action() const;

private:
  std::unique_ptr<ShowEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &   stream,
                                          const ShowEvent &event);
} // namespace KaliLaska
