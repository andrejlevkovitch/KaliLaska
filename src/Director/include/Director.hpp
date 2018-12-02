// Director.hpp

#pragma once

namespace KaliLaska {
/**\brief this class intended for manage events, sounds and many other. This is
the core of engine. Instance only once per program.
*/
class Director {
public:
  /**\brief use this function for get Director in you game
   * \return if Director was be instance return pointer ot it, else - nullptr
   */
  static Director *instance();
  /**\except if already was instance throw std::runtime_error
   */
  Director();
  ~Director();
  /**\brief start game loop
   * \return 0 if succes, and error value other wise
   */
  int exec();

private:
}; // namespace KaliLaska
} // namespace KaliLaska
