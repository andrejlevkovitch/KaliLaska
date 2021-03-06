// main.cpp

#include "KaliLaska/Application.hpp"
#include "WindowGL.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

#ifdef __SANITIZE_ADDRESS__
#  include <sanitizer/lsan_interface.h>
#endif

int main(int argc, char *argv[]) {
  assert(KaliLaska::Application::instance() == nullptr);

  KaliLaska::Application app{argc, argv};

  WindowGL w{"big screen with triangles", KaliLaska::Size{600, 600}};
  WindowGL w2{"mini screen with triangles", KaliLaska::Size{300, 200}};
  w2.setResizable(true);

  int retval = KaliLaska::Application::exec();

#ifdef __SANITIZE_ADDRESS__
  __lsan_do_leak_check();
  __lsan_disable();
#endif

  return retval;
}
