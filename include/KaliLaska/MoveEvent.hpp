// MoveEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MoveEventImp;
class EventFactory;

/**\brief the event generates when window has be moved
 */
class KALILASKA_EXPORT MoveEvent : public Event {
  friend EventFactory;

public:
  /**\brief konstructor for custom user events
   * \warning this is not move you window to new position!
   */
  explicit MoveEvent(Point curPos);

  ~MoveEvent() override;

  Point currentPos() const;

private:
  explicit MoveEvent(std::unique_ptr<MoveEventImp> imp);

private:
  std::unique_ptr<MoveEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &   stream,
                                          const MoveEvent &event);
} // namespace KaliLaska
