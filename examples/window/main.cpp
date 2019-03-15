// main.cpp

#include "KaliLaska/Application.hpp"
#include "MyWindow.hpp"
#include <cassert>
#include <cstdlib>

#ifdef __SANITIZE_ADDRESS__
#  include <sanitizer/lsan_interface.h>
#endif

int main(int argc, char *argv[]) {
  assert(KaliLaska::Application::instance() == nullptr);

  KaliLaska::Application app{argc, argv};

  MyWindow w{"temp", KaliLaska::Size{600, 600}};
  w.setFullScr();

  int retval = KaliLaska::Application::exec();

#ifdef __SANITIZE_ADDRESS__
  __lsan_do_leak_check();
  __lsan_disable();
#endif

  return retval;
}
