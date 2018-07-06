#pragma once

#include "draw/drawable.h"
#include "geometry/bbox.h"

class entity
{
public:
  /**
   * Create an entity with the given shape and position.
   * The entity is not selected and does not have a bounding box.
   */
  entity(drawable shape, point position);

  void draw(sdl_renderer& renderer, const point& pos) const;

  entity select() const;
  entity deselect() const;
  entity with_bbox(bounding_box bbox) const;
  entity move(const point& offset) const;

  bounding_box bbox() const;
  bool selected() const { return selected_; }

private:
  drawable shape_;
  point position_;
  bounding_box bbox_;
  bool selected_;
};

