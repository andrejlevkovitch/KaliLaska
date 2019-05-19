// BaseItem.hpp

#pragma once

#include "KaliLaska/GraphicsItem.hpp"

class BaseItem : public KaliLaska::GraphicsItem {
public:
  BaseItem()
      : anchor_{0, 0} {}

  void setAnchor(const KaliLaska::PointF &anchor) { anchor_ = anchor; }
  KaliLaska::PointF anchor() const { return anchor_; }

  void rotate(float angle) { KaliLaska::GraphicsItem::rotate(angle, anchor_); }

  void scale(float xFactor, float yFactor) {
    KaliLaska::GraphicsItem::scale(xFactor, yFactor, anchor_);
  }

protected:
  KaliLaska::PointF anchor_;
};
