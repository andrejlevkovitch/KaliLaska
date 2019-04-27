// main.cpp

#include "ExampleItem.hpp"
#include "ExampleScene.hpp"
#include "ExampleView.hpp"
#include "KaliLaska/Application.hpp"
#include "RingItem.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};

  ExampleView view2{"my two view", {900, 0}, {300, 300}};
  ExampleView view{"my graphics view", {0, 0}, {800, 800}};

  view.setResizable(true);
  view.setProperty(KaliLaska::GraphicsView::Property::Movable);
  view2.setProperty(KaliLaska::GraphicsView::Property::NotModificable |
                    KaliLaska::GraphicsView::Property::Movable);
  view2.setSceneBox(KaliLaska::Box{{-20, -20}, {800, 800}});

  ExampleScene scene{};
  view.setScene(&scene);
  view2.setScene(&scene);

  auto item1 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Blue);
  item1->setScenePos({0, 0}, {0, 0});
  auto item2 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Cyan);
  item2->setScenePos({700, 700}, {0, 0});
  auto item3 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Yellow);
  item3->setScenePos({0, 700}, {0, 0});
  auto item4 = std::make_shared<ExampleItem>(KaliLaska::Color::Colors::Magenta);
  item4->setScenePos({700, 0}, {0, 0});

  auto ringItem = std::make_shared<RingItem>();
  ringItem->setScenePos({400, 400}, {0, 0});

  auto childItem =
      std::make_shared<ExampleItem>(KaliLaska::Color::Colors::White);
  childItem->setParent(ringItem.get());
  childItem->setPos({50, 50});

  scene.addItem(item1);
  scene.addItem(item2);
  scene.addItem(item3);
  scene.addItem(item4);
  scene.addItem(ringItem);
  scene.addItem(childItem);

  int retval = app.exec();

  return retval;
}
