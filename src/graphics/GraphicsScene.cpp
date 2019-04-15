// GraphicsScene.cpp

#include "KaliLaska/GraphicsScene.hpp"
#include "GraphicsSceneImpFactory.hpp"
#include "KaliLaska/Application.hpp"
#include "KaliLaska/GraphicsItem.hpp"
#include "KaliLaska/KeyPressEvent.hpp"
#include "KaliLaska/KeyReleaseEvent.hpp"
#include "KaliLaska/MouseFocusEvent.hpp"
#include "KaliLaska/SceneMouseMoveEvent.hpp"
#include "KaliLaska/SceneMousePressEvent.hpp"
#include "KaliLaska/SceneMouseReleaseEvent.hpp"
#include "debug.hpp"
#include "imp/GraphicsSceneImp.hpp"
#include "logger/logger.hpp"

namespace bg = boost::geometry;

namespace KaliLaska {
GraphicsScene::GraphicsScene()
    : imp_{GraphicsSceneImpFactory::createImp()}
    , grabbed_{} {
  LOG_TRACE << "GraphicsScene: konstructor";
  Application::registerObject(this);
}

GraphicsScene::~GraphicsScene() {
  LOG_TRACE << "GraphicsScene: destructor";
  Application::unregisterObject(this);
}

GraphicsItem *GraphicsScene::itemAt(const PointF &                    pos,
                                    std::function<bool(float, float)> zcompare,
                                    Spatials spat) const {
  auto list = imp_->itemsAt(pos, spat);
  return *std::min_element(
      list.begin(),
      list.end(),
      [&zcompare](const GraphicsItem *lhs, const GraphicsItem *rhs) {
        if (zcompare(lhs->zvalue(), rhs->zvalue())) {
          return true;
          // TODO I am not sure that is it right?
        } else if (lhs->zvalue() == rhs->zvalue() &&
                   !zcompare(lhs->index_, rhs->index_)) {
          return true;
        }
        return false;
      });
}

std::list<GraphicsItem *>
GraphicsScene::itemsAt(const PointF &                    pos,
                       std::function<bool(float, float)> zcompare,
                       Spatials                          spat) const {
  auto retval = imp_->itemsAt(pos, spat);
  retval.sort([&zcompare](const GraphicsItem *lhs, const GraphicsItem *rhs) {
    if (zcompare(lhs->zvalue(), rhs->zvalue())) {
      return true;
    } else if (lhs->zvalue() == rhs->zvalue() &&
               !zcompare(lhs->index_, rhs->index_)) {
      return true;
    }
    return false;
  });
  return retval;
}

std::list<GraphicsItem *>
GraphicsScene::itemsAt(const Box &                       box,
                       std::function<bool(float, float)> zcompare,
                       Spatials                          spat) const {
  auto retval = imp_->itemsAt(box, spat);
  retval.sort([&zcompare](const GraphicsItem *lhs, const GraphicsItem *rhs) {
    if (zcompare(lhs->zvalue(), rhs->zvalue())) {
      return true;
    } else if (lhs->zvalue() == rhs->zvalue() &&
               !zcompare(lhs->index_, rhs->index_)) {
      return true;
    }
    return false;
  });
  return retval;
}

GraphicsItem *GraphicsScene::addItem(std::shared_ptr<GraphicsItem> item) {
  LOG_DEBUG << "GraphicsScene: add item " << item;
  if (item) {
    item->scene_ = this;
    if (auto retval = imp_->addItem(std::move(item))) {
      retval->index_ = lastIndex_++;
      return retval;
    }
  }
  return nullptr;
}

void GraphicsScene::removeItem(GraphicsItem *item) {
  LOG_DEBUG << "GraphicsScene: remove item " << item;
  imp_->removeItem(item);
}

void GraphicsScene::removeItem(const ConstIterator &iter) {
  LOG_DEBUG << "GraphicsScene: remove item " << *iter;
  imp_->removeItem(*(iter.imp_));
}

GraphicsScene::ConstIterator GraphicsScene::begin() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->begin())};
}

GraphicsScene::ConstIterator GraphicsScene::end() const {
  return ConstIterator{std::make_unique<SceneIterator>(imp_->end())};
}

size_t GraphicsScene::size() const {
  return imp_->size();
}

bool GraphicsScene::empty() const {
  return imp_->empty();
}

void GraphicsScene::clear() {
  LOG_TRACE;
  return imp_->clear();
}

Box GraphicsScene::bounds() const {
  return imp_->bounds();
}

void GraphicsScene::mouseMoveEvent(SceneMouseMoveEvent *event) {
  if (event && !event->accepted()) {
    if (grabbed_) {
      PointF anchor = event->previousPos();
      bg::subtract_point(anchor, grabbed_->scenePos());
      grabbed_->setScenePos(event->currentPos(), anchor);
      event->accept();
      return;
    }
    for (auto item : itemsAt(event->currentPos())) {
      item->mouseMoveEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mousePressEvent(SceneMousePressEvent *event) {
  if (event && !event->accepted()) {
    for (auto item : itemsAt(event->clickPos())) {
      item->mousePressEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mouseReleaseEvent(SceneMouseReleaseEvent *event) {
  if (event && !event->accepted()) {
    for (auto item : itemsAt(event->clickPos())) {
      item->mouseReleaseEvent(event);
      if (event->accepted()) {
        break;
      }
    }
  }
}

void GraphicsScene::mouseFocusEvent(MouseFocusEvent *event) {
  // TODO maybe here is a better way?
  // here if we lost focus I ungrab item, because when not ungrab it can have
  // unexpected rezult
  if (event && event->focus() == Mouse::Focus::Leave) {
    grabbItem(nullptr);
  }
}

void GraphicsScene::keyPressEvent(KeyPressEvent *event) {
  UNUSED(event);
}

void GraphicsScene::keyReleaseEvent(KeyReleaseEvent *event) {
  UNUSED(event);
}

void GraphicsScene::event(Event *event) {
  UNUSED(event);
}

void GraphicsScene::update() {
  // here we first copy pointers to all items because in update operation item
  // can change position
  std::list<GraphicsItem *> items;
  std::copy(this->begin(), this->end(), std::back_inserter(items));
  for (auto i : items) {
    i->update();
  }
}

void GraphicsScene::itemChanged(const GraphicsItem *item,
                                const PointF &      prevPos) {
  imp_->itemChanged(item, prevPos);
}

void GraphicsScene::grabbItem(GraphicsItem *item) {
  LOG_DEBUG << "GraphicsScene: item grabbed " << item;
  grabbed_ = item;
}

GraphicsItem *GraphicsScene::grabbedItem() const {
  return grabbed_;
}

void GraphicsScene::stackAbove(GraphicsItem *item) {
  if (item) {
    item->index_ = lastIndex_++;
  }
}
} // namespace KaliLaska
