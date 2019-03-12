// ResizeEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Size.hpp"
#include "KaliLaska/imp/ResizeEventImp.hpp"
#include <memory>

namespace KaliLaska {
class ResizeEvent final : public Event {
public:
  /**\brief use this constructor for create custom event.
   * \warning window will not be resized by this event if you set it manually to
   * you window! The event only notify about change size of window!
   */
  ResizeEvent(Size previousSize, Size newSize);

  /**\warning do not use this manually!
   */
  ResizeEvent(std::unique_ptr<ResizeEventImp> imp);

  Size previousSize() const;
  /**\return currently size, which was be set by this event
   */
  Size newSize() const;

private:
  std::unique_ptr<ResizeEventImp> imp_;
};

std::ostream &operator<<(std::ostream &stream, const ResizeEvent &event);
} // namespace KaliLaska
