#pragma once

#include "draw/color.h"
#include "geometry/height.h"
#include "geometry/width.h"

class sdl_renderer;

struct rectangle
{
  constexpr rectangle(width w, height h, color c):
    width_{w},
    height_{h},
    color_{c}
  {}
  
  void draw(sdl_renderer& renderer) const;

private:
  width width_;
  height height_;
  color color_;
};

inline void draw(const rectangle& rect, sdl_renderer& renderer)
{
  rect.draw(renderer);
}
