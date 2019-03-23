// ResizeEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Size.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class ResizeEventImp;
class EventFactory;

/**\brief generates after resizing of window
 */
class KALILASKA_EXPORT ResizeEvent final : public Event {
  friend EventFactory;

public:
  /**\brief use this constructor for create custom event.
   * \warning window will not be resized by this event if you set it manually to
   * you window! The event only notify about change size of window!
   */
  explicit ResizeEvent(Size newSize);

  ~ResizeEvent() override;

  /**\return currently size, which was be set by this event
   */
  Size currentSize() const;

private:
  explicit ResizeEvent(std::unique_ptr<ResizeEventImp> imp);

private:
  std::unique_ptr<ResizeEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &     stream,
                                          const ResizeEvent &event);
} // namespace KaliLaska
