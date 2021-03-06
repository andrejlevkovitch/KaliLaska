// GraphicsItem.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/Point.hpp"
#include "KaliLaska/Ring.hpp"
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

  /**\return box, which contains current item in item koordinates. Building from
   * shape. Rendering have to be in this box, otherwise it can have unexpected
   * rezult. Also item get mouse events from the box
   */
  Box boundingBox() const;

  /**\return bounding ring of current item in item koordinates. Uses for build
   * boundingBox. Ring have to be valid, otherwise it can have unexpected rezult
   *
   * \warning if you change the return value after inserting in scene - do not
   * forget call itemChanged method!
   */
  virtual Ring shape() const = 0;

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

  /**\param anchor position in item koordinates, relative to which will be get
   * all changes (change position, scale, rotation)
   */
  void setAnchor(const PointF &anchor);

  /**\return position (in item koordinates), relative to which all changes
   * happens (change position, scale, rotation). By default {0, 0}
   */
  PointF anchor() const;

  /**\return postion of item in parent koordinates relative to item anchor. If
   * parent is not set - in scene koordinates
   */
  PointF pos() const;

  /**\return position of item in scene koordinates relative to anchor
   */
  PointF scenePos() const;

  /**\brief set current postion of item in parent koordinates. If parent is
   * nullptr - in scene koordinates. Relative to item anchor
   */
  void setPos(const PointF &pos);

  /**\brief set current position of item in scene koordinates. Relative to item
   * anchor
   */
  void setScenePos(const PointF &pos);

  /**\param anchor relative to the position will be set new position of item.
   * Old anchor will not change. In item koordinates
   */
  void setScenePos(const PointF &pos, const PointF &anchor);

  /**\param angle in degrees, this value will be added for previous. Relative to
   * current anchor and z-axis
   */
  void rotate(float angle);

  /**\param anchor relative to the position will be rotate item. Old anchor will
   * not change. In item koordinates
   */
  void rotate(float angle, const PointF &anchor);

  /**\param angle in degrees, item will be rotated on the angle. Relative to
   * current anchor and z-axis
   */
  void setRotation(float angle);

  /**\param anchor relative to the position will be set rotation item. Old
   * anchor will not change. In item koordinates
   */
  void setRotation(float angle, const PointF &anchor);

  /**\return current rotate angle in degrees. Relative to z-axis
   */
  float angle() const;

  std::list<GraphicsItem *> children() const;

  /**\return current transformation matrix
   * \warning all changes of item (like change position) have to be from methods
   * of item, because it change postion of item in rtree
   */
  const TransformMatrix &matrix() const;

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

protected:
  /**\brief use this method if you need update item after unexpected change item
   * (for example if you change boundingBox or matrix)
   *
   * \param prevPos position, which contains bounding box (prefer centroid of
   * bounding box)
   *
   * \warning If you set uncorrect position, then
   * search of the item will be more long
   */
  void itemChanged(const PointF &prevPos) const;

private:
  void addToChildren(GraphicsItem *item);
  void removeFromChildren(GraphicsItem *item);

private:
  GraphicsScene *scene_;

  GraphicsItem *           parent_;
  std::set<GraphicsItem *> children_;

  TransformMatrix matrix_;
  PointF          anchor_;
};
} // namespace KaliLaska
