// View.cpp

#include "View.hpp"
#include "KaliLaska/AbstractGraphicsItem.hpp"
#include "KaliLaska/GraphicsScene.hpp"
#include "KaliLaska/MousePressEvent.hpp"
#include "KaliLaska/opengl.hpp"
#include "shaders.hpp"
#include <boost/qvm/mat_operations.hpp>
#include <filesystem>
#include <fstream>

namespace bq = boost::qvm;

View::View(std::string_view        title,
           const KaliLaska::Point &pos,
           const KaliLaska::Size & size)
    : AbstractGraphicsView{title, pos, size}
    , clearColor_{KaliLaska::Color::Colors::Black}
    , menu_{*this} {
  auto shaderCodeLoader = [](const std::filesystem::path &fileName) {
    std::string retval;
    if (!std::filesystem::exists(fileName) &&
        !std::filesystem::is_regular_file(fileName)) {
      throw std::runtime_error{"file not exists"};
    }
    std::ifstream fin;
    fin.open(fileName, std::ios::in);
    if (fin.is_open()) {
      std::copy(std::istreambuf_iterator<char>(fin),
                std::istreambuf_iterator<char>(),
                std::back_inserter(retval));
      fin.close();
    } else {
      throw std::runtime_error{"file with shader can not be opened"};
    }
    return retval;
  };

  std::string vertexShader   = shaderCodeLoader(vertexTexShaderFile);
  std::string fragmentShader = shaderCodeLoader(fragmentTexShaderFile);

  renderer()->registerProgram("texture", {vertexShader, fragmentShader});

  if (!renderer()->use("texture")) {
    std::runtime_error{"opengl program not valid"};
  }
  renderer()->setWinSize(drawSize());
  renderer()->blending(true);
}

void View::update() {
  if (scene()) {
    auto now = std::chrono::system_clock::now();
    if (auto duration = now - last_;
        duration >= std::chrono::milliseconds{50}) {
      render();
      last_ = std::chrono::system_clock::now();
    }
  }
}

void View::render() const {
  makeCurrent();

  renderer()->clear();
  renderer()->setViewMat(bq::inverse(matrix()));

  constexpr auto comparator = [](const KaliLaska::AbstractGraphicsItem *lhs,
                                 const KaliLaska::AbstractGraphicsItem *rhs) {
    if (lhs->zvalue() > rhs->zvalue() ||
        (lhs->zvalue() == rhs->zvalue() && !lhs->isAbove(rhs))) {
      return true;
    }
    return false;
  };

  for (const auto i : scene()->itemsAt(sceneBox(), comparator)) {
    i->render(renderer());
  }

  menu_.render();
  swapWindow();
}

void View::mousePressEvent(std::unique_ptr<KaliLaska::MousePressEvent> event) {
  if (scene() && event->button() & KaliLaska::Mouse::Button::Right) {
    if (auto item = scene()->itemAt(mapToScene(event->clickPos()))) {
      menu_.setImgui(item->contextMenu());
    }
  } else {
    if (menu_.isValid()) {
      menu_.setImgui(nullptr);
    }
    AbstractGraphicsView::mousePressEvent(std::move(event));
  }
}
