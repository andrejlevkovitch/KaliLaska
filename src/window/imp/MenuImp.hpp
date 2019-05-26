// MenuImp.hpp

#pragma once

#include <functional>
#include <string_view>

namespace KaliLaska {
class MenuImp {
public:
  virtual ~MenuImp() = default;

  virtual void setImgui(std::function<void(void)> function) = 0;
  virtual void render() const                               = 0;
  /**\return true if was set valid imgui function, othrewise - false
   */
  virtual bool isValid() const = 0;
};
} // namespace KaliLaska
