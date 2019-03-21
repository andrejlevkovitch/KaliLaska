// test_openGL.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "OpenGLWindow.hpp"

SCENARIO("Test openGL", "[OpenGLWindow]") {
  GIVEN("Application") {
    WHEN("We get window") {
      KaliLaska::Window *window{};

      REQUIRE_NOTHROW(window = new OpenGLWindow);

      THEN("Try update window") { REQUIRE_NOTHROW(window->update()); }
    }
  }
}
