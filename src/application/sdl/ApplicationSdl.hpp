// ApplicationSdl.hpp

#pragma once

#include "KaliLaska/imp/ApplicationImp.hpp"
#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>
#include <memory>

namespace KaliLaska {
class WindowSdlFactory;

/**\brief implementation of class Application
 */
class ApplicationSdl final : public ApplicationImp {
public:
  /**\throws if sdl can not be initialized
   */
  ApplicationSdl();
  ~ApplicationSdl();

  int exec() override;

  void exit(int code) override;

  WindowImpFactory *windowFactory() const override;
  EventImpFactory * eventFactory() const override;

private:
  std::atomic_bool loop_;
  std::atomic_int  return_code_;

  std::unique_ptr<WindowSdlFactory> windowFactory_;
  std::unique_ptr<EventImpFactory>  eventFactory_;
};
} // namespace KaliLaska
