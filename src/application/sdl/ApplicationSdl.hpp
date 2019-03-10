// ApplicationSdl.hpp

#pragma once

#include "KaliLaska/ApplicationImp.hpp"
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
  /**\except if sdl can not be initialized
   */
  ApplicationSdl();
  ~ApplicationSdl();

  int exec() override;

  void exit(int code) override;

  WindowImpFactory *windowFactory() const override;
  EventImpFactory * eventFactory() const override;

  int  ups() const override;
  void setUps(int ups) override;

  /**\brief handle sdl events
   */
  void handleEventQueue();

private:
  std::atomic<int>  cickleInterval_;
  std::atomic<bool> loop_;
  int               return_code_;

  std::unique_ptr<WindowSdlFactory> windowFactory_;
  std::unique_ptr<EventImpFactory>  eventFactory_;
};
} // namespace KaliLaska
