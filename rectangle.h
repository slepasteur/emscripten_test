#pragma once

#include "color.h"
#include "point.h"
#include "sdl_renderer.h"
#include "sdl_utils.h"

struct rectangle
{
  constexpr rectangle(point orig, int w, int h, color c):
    rect_{orig.x(), orig.y(), w, h},
    color_{c}
  {}
  
  void draw(sdl_renderer& renderer) const
  {
    set_render_color(color_, renderer);
    SDL_RenderDrawRect(renderer.value(), &rect_);
  }

private:
  SDL_Rect rect_;
  color color_;
};

inline void draw(const rectangle& rect, sdl_renderer& renderer)
{
  rect.draw(renderer);
}
