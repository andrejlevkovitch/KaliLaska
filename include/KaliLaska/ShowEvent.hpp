// ShowEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class ShowEventImp;
class EventFactory;

/**\brief represent window events AFTER some action
 */
class KALILASKA_EXPORT ShowEvent final : public Event {
  friend EventFactory;

public:
  explicit ShowEvent(ShowAction action);

  ~ShowEvent() override;

  ShowAction action() const;

private:
  explicit ShowEvent(std::unique_ptr<ShowEventImp> imp);

private:
  std::unique_ptr<ShowEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &   stream,
                                          const ShowEvent &event);
} // namespace KaliLaska
