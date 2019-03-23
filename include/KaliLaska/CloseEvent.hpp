// CloseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class CloseEventImp;
class EventFactory;

/**\brief generates before close window (for example when you push close button)
 */
class KALILASKA_EXPORT CloseEvent final : public Event {
  friend EventFactory;

public:
  /**\brief konsturctor for user custom events
   * \warning after window get this event you can not call the window
   */
  CloseEvent();

  ~CloseEvent() override;

private:
  explicit CloseEvent(std::unique_ptr<CloseEventImp> imp);

private:
  std::unique_ptr<CloseEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &    stream,
                                          const CloseEvent &event);
} // namespace KaliLaska
