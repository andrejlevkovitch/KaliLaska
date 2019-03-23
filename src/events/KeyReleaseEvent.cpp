// KeyReleaseEvent.cpp

#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KeyPrinter.hpp"
#include "imp/EventImpFactory.hpp"
#include "imp/KeyReleaseEventImp.hpp"

namespace KaliLaska {
KeyReleaseEvent::KeyReleaseEvent(Keyboard::Key       key,
                                 Keyboard::Modifyers modifyers)
    : Event{Type::KeyReleaseEvent}
    , imp_{Application::eventFactory()->createKeyReleaseEventImp(key,
                                                                 modifyers)} {
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

std::ostream &operator<<(std::ostream &stream, const KeyReleaseEvent &event) {
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
} // namespace KaliLaska
