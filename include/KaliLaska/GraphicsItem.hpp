// GraphicsItem.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/TransformMatrix.hpp"
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
  friend GraphicsScene;

public:
  GraphicsItem();
  virtual ~GraphicsItem() = default;

  GraphicsItem(GraphicsItem &&) = delete;
  GraphicsItem &operator=(GraphicsItem &&) = delete;

  /**\return box, which contains current item. Have to be in item koordinates.
   * Rendering have to be in this box, otherwise it can have unexpected rezult
   */
  virtual Box boundingBox() const = 0;

  /**\brief have to be used for rendering by opengl
   */
  virtual void render() const = 0;

  /**\brief this method calls by scene for evety object on scene. Usually it
   * calls every iteration of main loop. By default does nothing.
   */
  virtual void update();

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
  PointF pos() const;

  /**\return position of item in scene koordinates
   */
  PointF scenePos() const;

  /**\brief set current postion of item in parent koordinates. If parent is
   * nullptr - in scene koordinates
   */
  void setPos(const PointF &pos);

  /**\brief set current position of item in scene koordinates
   */
  void setScenePos(const PointF &pos);

  std::list<GraphicsItem *> children() const;

  const TransformMatrix &matrix() const;

protected:
  TransformMatrix &matrix();

protected:
  /**\brief by default does nothing
   */
  virtual void mouseMoveEvent(SceneMouseMoveEvent *event);
  /**\brief by default does nothing
   */
  virtual void mousePressEvent(SceneMousePressEvent *event);
  /**\brief by default does nothing
   */
  virtual void mouseReleaseEvent(SceneMouseReleaseEvent *event);

  /**\brief by default does nothing
   */
  virtual void userEvent(Event *event);

private:
  void addToChildren(GraphicsItem *item);
  void removeFromChildren(GraphicsItem *item);

private:
  GraphicsScene *scene_;

  GraphicsItem *           parent_;
  std::set<GraphicsItem *> children_;

  TransformMatrix matrix_;
};
} // namespace KaliLaska
