#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>

#include "rectangle.h"
#include "sdl_context.h"
#include "sdl_utils.h"


void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  clear_background(color::white(), ctx->renderer());

  rectangle border{{0, 0}, 800, 600, color::black()};
  draw(border, ctx->renderer());
  
  rectangle r{{50, 50}, 150, 75, color::red()};
  draw(r, ctx->renderer());

  render_present(ctx->renderer());
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  sdl_context ctx{800, 600};

  emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);

  return 0;
}
