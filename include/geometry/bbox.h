#pragma once

#include "point.h"
#include "width.h"
#include "height.h"

struct bounding_box
{
  /**
   * Constructs a bounding box from its top left and bottom right corners.
   */
  constexpr bounding_box(point tl, point br):
    top_left_(std::move(tl)),
    bottom_right_(std::move(br))
  {}

  /**
   * Constructs a bounding box from its top left corner, its witdth and its height.
   */
  constexpr bounding_box(point top_left, width w, height h):
   bounding_box(top_left, point(top_left.x() + w.val, top_left.y() + h.val))
  {}

  const point& top_left() const { return top_left_; }
  const point& bottom_right() const { return bottom_right_; }

private:
  point top_left_;
  point bottom_right_;
};

constexpr inline bool is_within(const point& p, const bounding_box& bbox)
{
  return bbox.top_left().x() <= p.x() && bbox.bottom_right().x() > p.x()
    && bbox.top_left().y() <= p.y() && bbox.bottom_right().y() > p.y();
}
