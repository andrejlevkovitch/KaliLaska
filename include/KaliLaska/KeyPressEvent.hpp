// KeyPressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KeyPressEventImp;
class EventFactory;

/**\brief generates after press some button
 */
class KALILASKA_EXPORT KeyPressEvent : public Event {
  friend EventFactory;

public:
  /**\brief konstructor for custom user events
   */
  KeyPressEvent(Keyboard::Key       key,
                Keyboard::Modifyers mode,
                bool                isRepeat = false);

  ~KeyPressEvent() override;

  /**\brief bit mask of currently pressed modifyers
   */
  Keyboard::Modifyers modifyers() const;

  /**\brief pressed key
   */
  Keyboard::Key key() const;

  /**\return true if the event is repeated (key was be pressed before)
   */
  bool isRepeat() const;

private:
  explicit KeyPressEvent(std::unique_ptr<KeyPressEventImp> imp);

private:
  std::unique_ptr<KeyPressEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &       stream,
                                          const KeyPressEvent &event);
} // namespace KaliLaska
