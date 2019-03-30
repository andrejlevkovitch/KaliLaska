// main.cpp

#include "ExampleItem.hpp"
#include "ExampleScene.hpp"
#include "ExampleView.hpp"
#include "KaliLaska/Application.hpp"
#include <iostream>

#ifdef __SANITIZE_ADDRESS__
#  include <sanitizer/lsan_interface.h>
#endif

int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};

  ExampleView  view{"my graphics view", {0, 0}, {800, 800}};
  ExampleScene scene{};
  view.setScene(&scene);

  auto item1 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Blue);
  item1->setPos({0, 0});
  auto item2 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Cyan);
  item2->setPos({100, 50});
  auto item3 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Yellow);
  item3->setPos({400, 800});
  auto item4 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Magenta);
  item4->setPos({-300, -20});

  scene.addItem(item1);
  scene.addItem(item2);
  scene.addItem(item3);
  scene.addItem(item4);

  int retval = app.exec();

#ifdef __SANITIZE_ADDRESS__
  __lsan_do_leak_check();
  __lsan_disable();
#endif

  return retval;
}
