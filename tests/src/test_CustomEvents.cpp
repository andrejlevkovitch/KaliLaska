// test_CustomEvents.cpp

#define CATCH_CONFIG_RUNNER
#include "KaliLaska/Application.hpp"
#include <catch2/catch.hpp>
int main(int argc, char *argv[]) {
  KaliLaska::Application app{argc, argv};
  int                    result = Catch::Session().run(argc, argv);
  return result;
}

#include "TestWindow.hpp"

using namespace KaliLaska;

const Event::Type customType =
    static_cast<Event::Type>(static_cast<int>(Event::Type::UserType) + 1);
class CustomEvent : public Event {
public:
  CustomEvent()
      : Event{customType} {}
};

SCENARIO("Test custom events", "[Event]") {
  // initialize window
  GIVEN("Window") {
    TestWindow *created{};
    REQUIRE_NOTHROW(created = new TestWindow{});
    TestWindow &window = *created;
    WHEN("Notify by CloseEvent") {
      Application::notify(&window, std::make_unique<CloseEvent>());
      THEN("Chek receive") { CHECK(window.closeEvent_ != nullptr); }
    }
    AND_WHEN("Notify by ShowEvent") {
      Application::notify(
          &window, std::make_unique<KaliLaska::ShowEvent>(ShowAction::Hidden));
      THEN("Check receive") {
        REQUIRE(window.showEvent_);
        CHECK(window.showEvent_->action() == ShowAction::Hidden);
      }
    }
    AND_WHEN("Notify by MoveEvent") {
      Point pos{390, 244};
      Application::notify(&window, std::make_unique<MoveEvent>(pos));
      THEN("Check recive") {
        REQUIRE(window.moveEvent_);
        CHECK(window.moveEvent_->currentPos() == pos);
      }
    }
    AND_WHEN("Notify by ResizeEvent") {
      Size size{500, 600};
      Application::notify(&window, std::make_unique<ResizeEvent>(size));
      THEN("Check recive") {
        REQUIRE(window.resizeEvent_);
        CHECK(window.resizeEvent_->currentSize() == size);
      }
    }
    AND_WHEN("Notify by MouseFocusEvent") {
      Application::notify(
          &window, std::make_unique<MouseFocusEvent>(Mouse::Focus::Leave));
      THEN("Check recive") {
        REQUIRE(window.mouseFocusEvent_);
        CHECK(window.mouseFocusEvent_->focus() == Mouse::Focus::Leave);
      }
    }
    AND_WHEN("Notify by MouseMoveEvent") {
      Mouse::Buttons buttons = Mouse::Button::Left | Mouse::Button::Middle;
      Point          prevPos{10, 580};
      Point          curPos{54, 367};
      Application::notify(
          &window, std::make_unique<MouseMoveEvent>(buttons, curPos, prevPos));
      THEN("Check recive") {
        REQUIRE(window.mouseMoveEvent_);
        CHECK(window.mouseMoveEvent_->buttons() == buttons);
        CHECK(window.mouseMoveEvent_->previousPos() == prevPos);
        CHECK(window.mouseMoveEvent_->currentPos() == curPos);
      }
    }
    AND_WHEN("Notify by MousePressEvent") {
      Mouse::Button button = Mouse::Button::Right;
      Mouse::Click  click  = Mouse::Click::Double;
      Point         pos{67, 34};
      Application::notify(
          &window, std::make_unique<MousePressEvent>(button, click, pos));
      THEN("Check recive") {
        REQUIRE(window.mousePressEvent_);
        CHECK(window.mousePressEvent_->button() == button);
        CHECK(window.mousePressEvent_->click() == click);
        CHECK(window.mousePressEvent_->clickPos() == pos);
      }
    }
    AND_WHEN("Notify by MouseReleaseEvent") {
      Mouse::Button button = Mouse::Button::Right;
      Point         pos{68, 37};
      Application::notify(&window,
                          std::make_unique<MouseReleaseEvent>(button, pos));

      THEN("Check recive") {
        REQUIRE(window.mouseReleaseEvent_);
        CHECK(window.mouseReleaseEvent_->clickPos() == pos);
        CHECK(window.mouseReleaseEvent_->button() == button);
      }
    }
    AND_WHEN("Notify by KeyboardFocusEvent") {
      Application::notify(
          &window,
          std::make_unique<KeyboardFocusEvent>(Keyboard::Focus::Gained));
      THEN("Check recive") {
        REQUIRE(window.keyboardFocusEvent_);
        CHECK(window.keyboardFocusEvent_->focus() == Keyboard::Focus::Gained);
      }
    }
    AND_WHEN("Notify by KeyPressEvent") {
      Keyboard::Modifyers modifyers = Keyboard::Mod::Alt;
      Application::notify(&window,
                          std::make_unique<KeyPressEvent>(
                              Keyboard::Key::Key_8, modifyers, true));
      THEN("Check receive") {
        REQUIRE(window.keyPressEvent_);
        CHECK(window.keyPressEvent_->key() == Keyboard::Key::Key_8);
        CHECK(window.keyPressEvent_->modifyers() == modifyers);
        CHECK(window.keyPressEvent_->isRepeat());
      }
    }
    AND_WHEN("Notify by KeyReleaseEvent") {
      Keyboard::Modifyers modifyers =
          Keyboard::Mod::Shift | Keyboard::Mod::Ctrl;
      Application::notify(
          &window,
          std::make_unique<KeyReleaseEvent>(Keyboard::Key::Key_J, modifyers));
      THEN("Check receive") {
        REQUIRE(window.keyReleaseEvent_);
        CHECK(window.keyReleaseEvent_->key() == Keyboard::Key::Key_J);
        CHECK(window.keyReleaseEvent_->modifyers() == modifyers);
      }
    }
    AND_WHEN("Notify by CustomEvent") {
      Application::notify(&window, std::make_unique<CustomEvent>());
      THEN("Check recive") {
        REQUIRE(window.userEvent_);
        CHECK(window.userEvent_->type() == customType);
      }
    }
  }
}
