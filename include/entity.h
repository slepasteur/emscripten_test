#pragma once

#include "draw/drawable.h"

class entity
{
public:
  entity(drawable shape, point position);

  void draw(sdl_renderer& renderer, const point& pos) const;

private:
  drawable shape_;
  point position_;
};

