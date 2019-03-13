// Application.hpp

#pragma once

#include <memory>

namespace KaliLaska {
class WindowImpFactory;
class EventImpFactory;

class Window;
class Event;

class ApplicationImp;

/**\brief initialize all parts of game engin and provide access to it. Singleton
 */
class Application final {
public:
  /**\brief you need set here input arguments of main, because it is needed for
   * load game libraries and create main window
   * \except in case repeted initialization
   */
  Application(int argc, char *argv[]);

  static Application *instance();

  ~Application();

  /**\return 0 if programm finish correctly
   * \except throw std::runtime_error if Application was not initialized
   * \brief event loop
   */
  static int exec();

  /**\brief break main loop and ser return value of this as code (return from
   * method exec)
   */
  static void exit(int code);

  /**\return abstract factory, which create implementaion for window
   */
  static WindowImpFactory *windowFactory();
  /**\return abstract factory, which create custom user events
   */
  static EventImpFactory *eventFactory();

  /**\brief send event to window
   */
  void notify(Window *, std::unique_ptr<Event> event) const;

private:
  void parseArguments(int argc, char *argv[]);

private:
  ApplicationImp *imp_;
};
} // namespace KaliLaska
