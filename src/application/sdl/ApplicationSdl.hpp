// ApplicationSdl.hpp

#pragma once

#include "application/imp/ApplicationImp.hpp"
#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <set>

namespace KaliLaska {
class WindowSdlFactory;
class EventSdlFactory;
class GraphicsSceneRTreeFactory;

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

  WindowImpFactory *       windowImpFactory() const override;
  EventImpFactory *        eventImpFactory() const override;
  GraphicsSceneImpFactory *graphicsSceneImpFactory() const override;

  void setIterationTimeInterval(std::chrono::milliseconds time) override;

  std::chrono::milliseconds iterationTimeInterval() const override;

  void registerObject(Object *obj) override;
  void unregisterObject(Object *obj) override;

private:
  void testWin() const;

private:
  std::atomic_bool loop_;
  std::atomic_int  return_code_;

  std::atomic_int iterationTime_;

  std::unique_ptr<WindowSdlFactory>          windowImpFactory_;
  std::unique_ptr<EventSdlFactory>           eventImpFactory_;
  std::unique_ptr<GraphicsSceneRTreeFactory> graphicsSceneImpFactory_;

  std::set<Object *> objects_;
};
} // namespace KaliLaska
