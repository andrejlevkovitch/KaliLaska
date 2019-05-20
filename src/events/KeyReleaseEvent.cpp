// KeyReleaseEvent.cpp

#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KeyPrinter.hpp"
#include "application/imp/ApplicationImp.hpp"
#include "events/imp/EventImpFactory.hpp"
#include "events/imp/KeyReleaseEventImp.hpp"

namespace KaliLaska {
KeyReleaseEvent::KeyReleaseEvent(Keyboard::Key       key,
                                 Keyboard::Modifyers modifyers)
    : Event{Type::KeyReleaseEvent}
    , imp_{Application::implementation()
               ->eventImpFactory()
               ->createKeyReleaseEventImp(key, modifyers)} {
}

KeyReleaseEvent::KeyReleaseEvent(std::unique_ptr<KeyReleaseEventImp> imp)
    : Event{Type::KeyReleaseEvent}
    , imp_{std::move(imp)} {
}

KeyReleaseEvent::~KeyReleaseEvent() {
}

Keyboard::Modifyers KeyReleaseEvent::modifyers() const {
  return imp_->modifyers();
}

Keyboard::Key KeyReleaseEvent::key() const {
  return imp_->key();
}
} // namespace KaliLaska

std::ostream &operator<<(std::ostream &                    stream,
                         const KaliLaska::KeyReleaseEvent &event) {
  using namespace KaliLaska;
  stream << "KeyReleaseEvent:";
  if (auto mod = event.modifyers(); mod != Keyboard::Mod::Invalid) {
    stream << ((mod & Keyboard::Mod::Alt) ? " Alt" : "");
    stream << ((mod & Keyboard::Mod::Shift) ? " Shift" : "");
    stream << ((mod & Keyboard::Mod::Ctrl) ? " Ctrl" : "");
  } else {
    stream << " None";
  }
  stream << ", key " << keyPrinter(event.key());
  return stream;
}
