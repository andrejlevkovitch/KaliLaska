// main.cpp

#include "KaliLaska/Application.hpp"
#include "KaliLaska/Window.hpp"
#include <cassert>
#include <cstdlib>

int main(int argc, char *argv[]) {
  assert(KaliLaska::Application::instance() == nullptr);

  KaliLaska::Application app{argc, argv};

  KaliLaska::Window w{"temp", KaliLaska::Size{600, 600}};

  return KaliLaska::Application::exec();
}
