#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>

#include "rectangle.h"
#include "line.h"
#include "sdl_context.h"
#include "sdl_utils.h"


void process_input()
{
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYUP:
        break;
    }
  }
}

void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  clear_background(color::white(), ctx->renderer());

  for (const auto& e : ctx->entities())
  {
    draw(e, ctx->renderer());
  }

  render_present(ctx->renderer());
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  auto ctx = sdl_context{800, 600}
    .add_entity(drawable(rectangle({0, 0}, 800, 600, color::black())))
    .add_entity(drawable(rectangle({50, 50}, 150, 75, color::red())))
    .add_entity(drawable(line({300, 200}, {500, 400}, color::blue())));

  emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);

  return 0;
}

