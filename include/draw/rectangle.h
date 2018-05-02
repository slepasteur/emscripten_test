#pragma once

#include "draw/color.h"
#include "geometry/height.h"
#include "geometry/width.h"
#include "geometry/point.h"

class sdl_renderer;

struct rectangle
{
  constexpr rectangle(width w, height h, color c):
    width_{w},
    height_{h},
    color_{c}
  {}
  
  void draw(sdl_renderer& renderer, const point& pos) const;

private:
  width width_;
  height height_;
  color color_;
};

