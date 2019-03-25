// GraphicsSceneImp.hpp

#pragma once

#include "KaliLaska/Point.hpp"
#include <iterator>
#include <list>
#include <memory>

namespace KaliLaska {
class GraphicsItem;

class SceneIteratorImp;

/**\brief implementation of GraphicsScene
 */
class GraphicsSceneImp {
public:
  virtual ~GraphicsSceneImp() = default;

  /**\return item which contains this position. If there are several items -
   * return at front plane item
   * \param pos scene position
   */
  virtual GraphicsItem *itemAt(const Point &pos) const = 0;
  /**\return all items which contains this postion. First will be items at front
   * plane
   */
  virtual std::list<GraphicsItem *> itemsAt(const Point &pos) const = 0;

public:
  class SceneIterator final
      : public std::iterator<std::forward_iterator_tag, GraphicsItem *> {
  public:
    explicit SceneIterator(std::unique_ptr<SceneIteratorImp> imp);
    ~SceneIterator();

    GraphicsItem *operator*() const;
    GraphicsItem *operator->() const;

    SceneIterator &operator++();
    SceneIterator &operator++(int);

    SceneIterator(const SceneIterator &rhs) = delete;
    SceneIterator &operator=(const SceneIterator &rhs) = delete;

    SceneIterator(SceneIterator &&rhs);
    SceneIterator &operator=(SceneIterator &&rhs);

  private:
    std::unique_ptr<SceneIteratorImp> imp_;
  };

public:
  virtual SceneIterator begin() const = 0;
  virtual SceneIterator end() const   = 0;
};
} // namespace KaliLaska

namespace std {
template <>
struct iterator_traits<KaliLaska::GraphicsSceneImp::SceneIterator> {
  using iterator_category = std::forward_iterator_tag;
  using value_type        = KaliLaska::GraphicsItem *;
  using pointer           = KaliLaska::GraphicsItem *;
  using reference         = KaliLaska::GraphicsItem *;
};
} // namespace std
