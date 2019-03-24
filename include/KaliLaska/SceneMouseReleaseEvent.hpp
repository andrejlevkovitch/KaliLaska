// SceneMouseReleaseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseReleaseEvent;

class SceneMouseReleaseEvent : public Event {
public:
  explicit SceneMouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event);

  ~SceneMouseReleaseEvent();

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;

  /**\return click position in scene coordinates
   */
  Point clickPos() const;

  /**\return click position in view coordinates
   */
  Point clickViewPos() const;

private:
  std::unique_ptr<MouseReleaseEvent> event_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &                           stream,
           const KaliLaska::SceneMouseReleaseEvent &event);
