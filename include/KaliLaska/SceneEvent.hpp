// SceneEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"

namespace KaliLaska {
class SceneEvent : public Event {
public:
  using Event::Event;
  ~SceneEvent() override = default;
  /**\brief some events can be addressed to many objects, so if object use this
   * event it can set accept of the event and event will not be get by other
   * object.
   *
   * \return true if event was be accepted
   */
  bool accepted() const { return accepted_; }
  void accept() { accepted_ = true; }

private:
  bool accepted_ = false;
};
} // namespace KaliLaska
