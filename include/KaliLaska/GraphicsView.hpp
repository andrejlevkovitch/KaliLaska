// GraphicsView.hpp

#pragma once

#include "KaliLaska/Box.hpp"
#include "KaliLaska/TransformMatrix.hpp"
#include "KaliLaska/Window.hpp"

namespace KaliLaska {
class GraphicsScene;
class ViewState;

class MoveSceneState;
class UnModificableState;
class NotifySceneState;

/**\brief display entity of GraphicsScen. One view can display only one scene
 */
class GraphicsView : public Window {
  friend UnModificableState;
  friend NotifySceneState;
  friend MoveSceneState;

public:
  enum Property : uint8_t {
    None = 0,
    /**\brief if set this, then view not notify scene about any events
     */
    NotModificable = 1,
    /**\brief if scene mouse event was not be accepted, then sceneBox will be
     * changed
     */
    Movable = 2
  };
  using Properties = uint8_t;

  GraphicsView(std::string_view title, const Point &pos, const Size &size);
  ~GraphicsView() override = default;

  /**\brief by default view have several properties (look in Property enum),
   * which you can set by the method
   */
  void setProperty(Properties prop);

  /**\warning not set ownershiep of scene
   * \brief view can have only one scene at time
   */
  virtual void   setScene(GraphicsScene *scene);
  GraphicsScene *scene() const;

  /**\brief by default equal to viewBox
   * \param sceneBox rectangle which will be displayed be the view
   */
  void setSceneBox(const Box &sceneBox);
  Box  sceneBox() const;

  /**\return box in view koordinates {0, 0, width, height}
   */
  Box viewBox() const;

  /**\return constant matrix of the view
   */
  const TransformMatrix &matrix() const;

  /**\param anchor position of view, relative to it will be scaled.
   * \brief scale sceneBox relatively to previous scale.
   */
  void scale(std::pair<float, float> factors, const PointF &anchor);

  /**\brief set current scale.
   */
  void setScale(std::pair<float, float> factors, const PointF &anchor);

  /**\return current x&y scale factors
   */
  std::pair<float, float> getScale() const;

  /**\brief rotate sceneBox relative to previous rotation
   * \param angle in radians
   */
  void rotate(float angle, const PointF &anchor);

  /**\brief set rotation for sceneBox
   * \param angle in radians
   */
  void setRotation(float angle, const PointF &anchor);

  /**\return angle in radians
   */
  float getRotation() const;

protected:
  /**\return not constant matrix of the view
   */
  TransformMatrix &matrixC();

protected:
  /**\brief notify scene about event
   */
  void mousePressEvent(std::unique_ptr<MousePressEvent> event) override;
  /**\brief notify scene about event
   */
  void mouseReleaseEvent(std::unique_ptr<MouseReleaseEvent> event) override;
  /**\brief notify scene about event
   */
  void mouseMoveEvent(std::unique_ptr<MouseMoveEvent> event) override;

  /**\brief notify scene about event
   */
  void keyPressEvent(std::unique_ptr<KeyPressEvent> event) override;
  /**\brief notify scene about event
   */
  void keyReleaseEvent(std::unique_ptr<KeyReleaseEvent> event) override;

  /**\brief notify scene about event
   */
  void mouseFocusEvent(std::unique_ptr<MouseFocusEvent> event) override;

private:
  void changeState(ViewState *state);

private:
  GraphicsScene *scene_;

  /**\brief tranform view koords in scene koords
   */
  TransformMatrix matrix_;

  ViewState *state_;

  Properties properties_;
};
} // namespace KaliLaska
