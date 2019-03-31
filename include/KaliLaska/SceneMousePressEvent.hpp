// SceneMousePressEvent.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/SceneEvent.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MousePressEvent;

class SceneMousePressEvent : public SceneEvent {
public:
  SceneMousePressEvent(std::unique_ptr<MousePressEvent> event,
                       const TransformMatrix &          matrix);

  ~SceneMousePressEvent() override;

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;

  Mouse::Click click() const;

  /**\return click position in scene coordinates
   */
  PointF clickPos() const;

  /**\return click position in view coordinates
   */
  Point clickViewPos() const;

private:
  std::unique_ptr<MousePressEvent> event_;
  TransformMatrix                  matrix_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::SceneMousePressEvent &event);
