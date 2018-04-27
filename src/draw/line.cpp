#include "draw/line.h"

#include "sdl/sdl_renderer.h"
#include "sdl/sdl_utils.h"

void line::draw(sdl_renderer& renderer) const
{
  set_render_color(color_, renderer);
  SDL_RenderDrawLine(renderer.value(), begin_.x(), begin_.y(), end_.x(), end_.y());
}

