// main.cpp

#include "KaliLaska/Application.hpp"
#include "MyWindow.hpp"
#include <cassert>
#include <cstdlib>

int main(int argc, char *argv[]) {
  assert(KaliLaska::Application::instance() == nullptr);

  KaliLaska::Application app{argc, argv};

  MyWindow w{"temp", KaliLaska::Size{600, 600}};

  int retval = KaliLaska::Application::exec();

  return retval;
}
