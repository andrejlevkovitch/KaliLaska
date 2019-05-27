// SceneMouseReleaseEvent.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/SceneEvent.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseReleaseEvent;

class SceneMouseReleaseEvent : public SceneEvent {
public:
  SceneMouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event,
                         const TransformMatrix &            matrix);

  ~SceneMouseReleaseEvent() override;

  Mouse::Button  button() const;
  Mouse::Buttons buttons() const;

  /**\return click position in scene coordinates
   */
  PointF clickPos() const;

  /**\return click position in view coordinates
   */
  Point clickViewPos() const;

  /**\return transformation matrix, which translate view points to scene points
   */
  const TransformMatrix &matrix() const;

private:
  std::unique_ptr<MouseReleaseEvent> event_;
  TransformMatrix                    matrix_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &                           stream,
           const KaliLaska::SceneMouseReleaseEvent &event);
