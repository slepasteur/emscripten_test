#pragma once

#include "color.h"
#include "point.h"
#include "sdl_renderer.h"
#include "sdl_utils.h"

struct line
{
  constexpr line(point begin, point end, color c):
    begin_{begin},
    end_{end},
    color_{c}
  {}
  
  void draw(sdl_renderer& renderer) const
  {
    set_render_color(color_, renderer);
    SDL_RenderDrawLine(renderer.value(), begin_.x(), begin_.y(), end_.x(), end_.y());
  }

private:
  point begin_;
  point end_;
  color color_;
};

inline void draw(const line& l, sdl_renderer& renderer)
{
  l.draw(renderer);
}

