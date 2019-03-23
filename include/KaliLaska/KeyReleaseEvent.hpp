// KeyReleaseEvent.hpp

#pragma once

#include "KaliLaska/Event.hpp"
#include "kalilaska_export.h"
#include <memory>

namespace KaliLaska {
class KeyReleaseEventImp;
class EventFactory;

/**\brief generates after release some button
 */
class KALILASKA_EXPORT KeyReleaseEvent final : public Event {
  friend EventFactory;

public:
  /**\brief konstructor for custom user events
   */
  KeyReleaseEvent(Keyboard::Key key, Keyboard::Modifyers modifyers);

  ~KeyReleaseEvent() override;

  /**\brief return currently pressed modifyers
   */
  Keyboard::Modifyers modifyers() const;

  /**\brief return released key
   */
  Keyboard::Key key() const;

private:
  explicit KeyReleaseEvent(std::unique_ptr<KeyReleaseEventImp> event);

private:
  std::unique_ptr<KeyReleaseEventImp> imp_;
};

KALILASKA_EXPORT std::ostream &operator<<(std::ostream &         stream,
                                          const KeyReleaseEvent &event);
} // namespace KaliLaska
