// ApplicationSdl.hpp

#pragma once

#include "application/imp/ApplicationImp.hpp"
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

  void setIterationTimeInterval(std::chrono::milliseconds time) override;

  std::chrono::milliseconds iterationTimeInterval() const override;

private:
  std::atomic_bool loop_;
  std::atomic_int  return_code_;

  std::atomic_int iterationTime_;

  std::unique_ptr<WindowSdlFactory> windowFactory_;
  std::unique_ptr<EventImpFactory>  eventFactory_;
};
} // namespace KaliLaska
