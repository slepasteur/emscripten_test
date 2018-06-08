#pragma once

#include "draw/drawable.h"

class entity
{
public:
  entity(drawable shape, point position, bool selected = false);

  void draw(sdl_renderer& renderer, const point& pos) const;
  entity select() const;
  entity deselect() const;
  entity move(const point& offset) const;

  bool selected() const { return selected_; }

private:
  drawable shape_;
  point position_;
  bool selected_;
};

