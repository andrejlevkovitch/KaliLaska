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

namespace GL {
class Renderer;
}

/**\brief represent graphical objects on scene
 */
class GraphicsItem {
  friend GraphicsScene;

public:
  enum ItemType { None = 0, UserType = 100 };

  GraphicsItem();
  virtual ~GraphicsItem();

  GraphicsItem(GraphicsItem &&) = delete;
  GraphicsItem &operator=(GraphicsItem &&) = delete;

  /**\return type of item. By default None. If you want to set you own type -
   * use UserType
   */
  virtual ItemType type() const;

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

  /**\brief have to be used for rendering by GL::Renderer (you also can use
   * opengl directly)
   */
  virtual void render(GL::Renderer *renderer) const = 0;

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

  /**\return postion (top-left corner) of item in parent koordinates. If parent
   * is not set - in scene koordinates
   */
  PointF pos() const;

  /**\return position (top-left corner) of item in scene koordinates.
   */
  PointF scenePos() const;

  /**\brief set current postion of item in parent koordinates. If parent is
   * nullptr - in scene koordinates.
   */
  void setPos(const PointF &pos);

  /**\param anchor relative to the position will be set new position of item.
   * In item koordinates
   */
  void setScenePos(const PointF &pos, const PointF &anchor);

  /**\param anchor relative to the position will be rotate item. In item
   * koordinates
   * \param angle in radians
   */
  void rotate(float angle, const PointF &anchor);

  /**\param anchor relative to the position will be set rotation item. In item
   * koordinates
   * \param angle in radians
   */
  void setRotation(float angle, const PointF &anchor);

  /**\return current rotate angle in radians. Relative to z-axis
   */
  float getRotation() const;

  /**\brief scale current item relative to anchor. Relative to current scale.
   */
  void scale(float xFactor, float yFactor, const PointF &anchor);
  void scale(std::pair<float, float> factors, const PointF &anchor);

  /**\brief set current scale
   */
  void setScale(float xFactor, float yFactor, const PointF &anchor);
  void setScale(std::pair<float, float> factors, const PointF &anchor);

  /**\return current x&y scale factors of item.
   */
  std::pair<float, float> getScale() const;

  std::list<GraphicsItem *> children() const;

  /**\return current transformation matrix
   * \warning all changes of item (like change position) have to be from methods
   * of item, because it change postion of item in rtree
   */
  const TransformMatrix &matrix() const;

  /**\return by default - 0
   */
  float zvalue() const;

  /**\brief greather value mens the object is further from the observer.
   */
  void setZvalue(unsigned short val);

  /**\brief set the item above other items whith same zvalue
   */
  void stackAbove();

  /**\return  true if current item is above rhs-item. If rhs is nullptr or items
   * not from one scene - return false
   */
  bool isAbove(const GraphicsItem *rhs) const;

  // FIXME not preaty
  /**\return implementation for Menu
   */
  virtual std::function<void(void)> contextMenu();

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

  /**\warning be careful in change matrix! If you change some value in matrix
   * you have to call itemChanged method!
   */
  TransformMatrix &matrixC();

private:
  void addToChildren(GraphicsItem *item);
  void removeFromChildren(GraphicsItem *item);

private:
  GraphicsScene *scene_;

  GraphicsItem *           parent_;
  std::set<GraphicsItem *> children_;

  TransformMatrix matrix_;

  size_t         index_;
  unsigned short zvalue_;
};
} // namespace KaliLaska
