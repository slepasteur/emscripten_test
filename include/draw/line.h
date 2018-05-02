#pragma once

#include "draw/color.h"
#include "geometry/point.h"

class sdl_renderer;

struct line
{
  constexpr line(point begin, point end, color c):
    begin_{begin},
    end_{end},
    color_{c}
  {}
  
  void draw(sdl_renderer& renderer, const point& pos) const;

private:
  point begin_;
  point end_;
  color color_;
};

