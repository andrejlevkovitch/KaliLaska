// KeyPressEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "KaliLaska/imp/KeyPressEventImp.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KALILASKA_EXPORT KeyPressEvent : public Event {
public:
  /**\brief konstructor for custom user events
   */
  KeyPressEvent(Keyboard::Key       key,
                Keyboard::Modifyers mode,
                bool                isRepeat = false);

  KeyPressEvent(std::unique_ptr<KeyPressEventImp> imp);

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
  std::unique_ptr<KeyPressEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &       stream,
                                          const KeyPressEvent &event);
} // namespace KaliLaska
