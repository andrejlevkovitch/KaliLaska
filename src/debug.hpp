// debug.hpp

#pragma once

#include <iostream>

#define UNUSED(x) (void)x

#define DEBUG_OUT(x) std::cerr << x << std::endl;

#define GET_POSITION()                                                         \
  std::cerr << __FILE__ << ':' << __LINE__ << ' ' << __FUNCTION__ << std::endl;
