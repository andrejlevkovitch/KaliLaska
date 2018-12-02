// Director.cpp

#include "Director.hpp"
#include "stdexcept"

namespace KaliLaska {

static Director *pointer_to_Director_imp = nullptr;

Director::Director() {
  if (pointer_to_Director_imp) {
    throw std::runtime_error{"class Director can instance only once!"};
  }
  pointer_to_Director_imp = this;
}

Director::~Director() {}

Director *Director::instance() { return pointer_to_Director_imp; }
} // namespace KaliLaska
