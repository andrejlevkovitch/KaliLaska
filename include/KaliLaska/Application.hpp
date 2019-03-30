// Application.hpp

#pragma once

#include "kalilaska_export.h"
#include <chrono>
#include <memory>

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;
class GraphicsSceneImpFactory;

class Window;
class Event;

class Object;

class ApplicationImp;

/**\brief initialize all parts of game engin and provide access to it. Singleton
 */
class KALILASKA_EXPORT Application final {
public:
  /**\brief you need set here input arguments of main, because it is needed for
   * load game libraries and create main window. Also initialize opengl library
   * (by gl3w) \throws in case repeted initialization
   */
  Application(int argc, char *argv[]);

  static Application *instance();

  ~Application();

  /**\return EXIT_SUCCESS if programm finish correctly, EXIT_FAILURE - otherwise
   * \throws std::runtime_error if Application was not initialized
   * \brief event loop
   */
  static int exec();

  /**\brief break main loop and ser return value of this as code (return from
   * method exec)
   */
  static void exit(int code);

  /**\return abstract factory, which create implementaion for window.
   */
  static WindowImpFactory *windowFactory();
  /**\return abstract factory, which create custom user events
   */
  static EventImpFactory *eventFactory();

  /**\brief send event to window. This event will be delivered momentally (in
   * current iteration of the main cikle).
   * \warning custom user event as MoveEvent or ResizeEvent will not change
   * window. This events only notify about changing
   */
  static void notify(Window *window, std::unique_ptr<Event> event);

  /**\brief set duration time of every iteration of cickle. By default - 50
   * milliseconds
   *
   * \param time duration of iteration in milliseconds
   */
  void setIterationTimeInterval(std::chrono::milliseconds time);

  /**\return current time interval of main cickle
   */
  std::chrono::milliseconds iterationTimeInterval() const;

  /**\brief registered object call by the application every loop iteration
   */
  static void registerObject(Object *obj);
  static void unregisterObject(Object *obj);

private:
  void parseArguments(int argc, char *argv[]);

private:
  std::unique_ptr<ApplicationImp> imp_;
};
} // namespace KaliLaska
