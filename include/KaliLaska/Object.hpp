// Object.hpp

#pragma once

namespace KaliLaska {
class Object {
public:
  virtual ~Object()     = default;
  virtual void update() = 0;
};
} // namespace KaliLaska
