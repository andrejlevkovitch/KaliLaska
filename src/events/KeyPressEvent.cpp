// KeyPressEvent.cpp

#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/imp/EventImpFactory.hpp"
#include "KeyPrinter.hpp"

namespace KaliLaska {
KeyPressEvent::KeyPressEvent(Keyboard::Key       key,
                             Keyboard::Modifyers mode,
                             bool                isRepeat)
    : Event{Type::KeyPressEvent}
    , imp_{Application::eventFactory()->createKeyPressEventImp(
          key, mode, isRepeat)} {
}

KeyPressEvent::KeyPressEvent(std::unique_ptr<KeyPressEventImp> imp)
    : Event{Type::KeyPressEvent}
    , imp_{std::move(imp)} {
}

Keyboard::Modifyers KeyPressEvent::modifyers() const {
  return imp_->modifyers();
}

Keyboard::Key KeyPressEvent::key() const {
  return imp_->key();
}

bool KeyPressEvent::isRepeat() const {
  return imp_->isRepeat();
}

std::ostream &operator<<(std::ostream &stream, const KeyPressEvent &event) {
  stream << "KeyPressEvent: mod";
  if (auto mod = event.modifyers(); mod != Keyboard::Mod::Invalid) {
    stream << ((mod & Keyboard::Mod::Alt) ? " Alt" : "");
    stream << ((mod & Keyboard::Mod::Shift) ? " Shift" : "");
    stream << ((mod & Keyboard::Mod::Ctrl) ? " Ctrl" : "");
  } else {
    stream << " None";
  }
  stream << ", key " << keyPrinter(event.key())
         << (event.isRepeat() ? " , repeated" : "");
  return stream;
}
} // namespace KaliLaska
