#include "draw/rectangle.h"

#include "sdl/sdl_renderer.h"
#include "sdl/sdl_utils.h"

void rectangle::draw(sdl_renderer& renderer, const point& pos) const
{
  SDL_Rect rect{pos.x(), pos.y(), width_.val, height_.val};
  set_render_color(color_, renderer);
  SDL_RenderDrawRect(renderer.value(), &rect);
}

