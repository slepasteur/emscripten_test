#include "draw/rectangle.h"

#include "sdl/sdl_renderer.h"
#include "sdl/sdl_utils.h"

void rectangle::draw(sdl_renderer& renderer) const
{
  SDL_Rect rect{0, 0, width_.val, height_.val};
  set_render_color(color_, renderer);
  SDL_RenderDrawRect(renderer.value(), &rect);
}

