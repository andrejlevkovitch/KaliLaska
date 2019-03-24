// SceneMousePressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/Point.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MousePressEvent;

class SceneMousePressEvent : public Event {
public:
  explicit SceneMousePressEvent(std::unique_ptr<MousePressEvent> event);

  ~SceneMousePressEvent() override;

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;

  Mouse::Click click() const;

  /**\return click position in scene coordinates
   */
  Point clickPos() const;

  /**\return click position in view coordinates
   */
  Point clickViewPos() const;

private:
  std::unique_ptr<MousePressEvent> event_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::SceneMousePressEvent &event);
