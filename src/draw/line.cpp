#include "draw/line.h"

#include "sdl/sdl_renderer.h"
#include "sdl/sdl_utils.h"

void line::draw(sdl_renderer& renderer, const point& pos) const
{
  set_render_color(color_, renderer);
  auto begin = begin_ + pos;
  auto end = end_ + pos;
  SDL_RenderDrawLine(renderer.value(), begin.x(), begin.y(), end.x(), end.y());
}

