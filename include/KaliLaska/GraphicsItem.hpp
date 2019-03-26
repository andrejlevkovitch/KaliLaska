// GraphicsItem.hpp

#pragma once

#include <KaliLaska/Point.hpp>
#include <list>
#include <memory>
#include <set>

namespace KaliLaska {
class Event;

class SceneMouseMoveEvent;
class SceneMousePressEvent;
class SceneMouseReleaseEvent;

class GraphicsScene;

/**\brief represent graphical objects on scene
 */
class GraphicsItem {
public:
  GraphicsItem();
  virtual ~GraphicsItem() = default;

  GraphicsItem(GraphicsItem &&) = delete;
  GraphicsItem &operator=(GraphicsItem &&) = delete;

  /**\return scene where currently be the element or nullptr if not assotiated
   * with any scene
   */
  GraphicsScene *scene() const;

  /**\return parent GraphicsItem if it was be set, otherwise nullptr. Parent
   * item set ownershiep of the item, so it parent item will be changed
   * (position for example), or will be deleted - it happens with child item
   */
  GraphicsItem *parent() const;

  void setParent(GraphicsItem *parent);

  /**\return postion of item in parent koordinates. If parent is not set - in
   * scene koordinates
   */
  Point pos() const;

  /**\return position of item in scene koordinates
   */
  Point scenePos() const;

  /**\brief set current postion of item in parent koordinates. If parent is
   * nullptr - in scene koordinates
   */
  void setPos(const Point &pos);

  /**\brief set current position of item in scene koordinates
   */
  void setScenePos(const Point &pos);

  std::list<GraphicsItem *> children() const;

protected:
  virtual void mouseMoveEvent(std::unique_ptr<SceneMouseMoveEvent> event);
  virtual void mousePressEvent(std::unique_ptr<SceneMousePressEvent> event);
  virtual void mouseReleaseEvent(std::unique_ptr<SceneMouseReleaseEvent> event);

  virtual void userEvent(std::unique_ptr<Event> event);

private:
  void addToChildren(GraphicsItem *item);
  void removeFromChildren(GraphicsItem *item);

private:
  GraphicsScene *scene_;

  GraphicsItem *           parent_;
  std::set<GraphicsItem *> children_;
};
} // namespace KaliLaska
