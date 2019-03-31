// SceneMouseMoveEvent.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include "KaliLaska/SceneEvent.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class MouseMoveEvent;

/**\brief translate MouseMoveEvent from View to Scene
 */
class KALILASKA_EXPORT SceneMouseMoveEvent : public SceneEvent {
public:
  SceneMouseMoveEvent(std::unique_ptr<MouseMoveEvent> event,
                      const TransformMatrix &         matrix);

  ~SceneMouseMoveEvent() override;

  Mouse::Buttons buttons() const;

  /**\return current cursor position in scene koordinates
   */
  PointF currentPos() const;
  /**\return previous cursor position in scene koordinates
   */
  PointF previousPos() const;

  /**\return current position in view koordinates
   */
  Point currentViewPos() const;
  /**\return previous position in view koordinates
   */
  Point previousViewPos() const;

private:
  std::unique_ptr<MouseMoveEvent> event_;
  TransformMatrix                 matrix_;
};
} // namespace KaliLaska

KALILASKA_EXPORT std::ostream &
                 operator<<(std::ostream &stream, const KaliLaska::SceneMouseMoveEvent &event);
