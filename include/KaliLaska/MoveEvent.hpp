// MoveEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/MoveEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
/**\brief the event generates when window has be moved
 */
class KALILASKA_EXPORT MoveEvent : public Event {
public:
  /**\brief konstructor for custom user events
   * \warning this is not move you window to new position!
   */
  MoveEvent(Point curPos);

  MoveEvent(std::unique_ptr<MoveEventImp> imp);

  Point currentPos() const;

private:
  std::unique_ptr<MoveEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &   stream,
                                          const MoveEvent &event);
} // namespace KaliLaska
