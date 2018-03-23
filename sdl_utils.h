#pragma once

#include "color.h"
#include "sdl_renderer.h"

inline void set_render_color(const color& c, sdl_renderer& renderer)
{
  SDL_SetRenderDrawColor(renderer.value(), c.r(), c.g(), c.b(), c.a());
}

inline void clear_background(const color& c, sdl_renderer& renderer)
{
  set_render_color(c, renderer);
  SDL_RenderClear(renderer.value());
}

inline void render_present(sdl_renderer& renderer)
{
  SDL_RenderPresent(renderer.value());
}
