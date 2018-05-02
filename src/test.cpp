#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <variant>

#include "draw/rectangle.h"
#include "draw/line.h"
#include "sdl/sdl_context.h"
#include "sdl/sdl_utils.h"
#include "action.h"

#include "overloaded.h"

point pos;

void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  auto actions = intents();

  for (const auto& a : actions)
  {
    std::visit(overloaded {
        [](up){ std::cout << "up\n";  pos = pos - point{0, 1}; },
        [](down){ std::cout << "down\n"; pos = pos + point{0, 1}; },
        [](left){ std::cout << "left\n"; pos = pos - point{1, 0}; },
        [](right){ std::cout << "right\n"; pos = pos + point{1, 0}; },
        }, a);
  }

  clear_background(color::white(), ctx->renderer());

  for (const auto& e : ctx->current_model().entities())
  {
    draw(e, ctx->renderer(), pos);
  }

  render_present(ctx->renderer());
}

void run()
{
  SDL_Init(SDL_INIT_VIDEO);

  auto ctx = sdl_context{800, 600};

  auto m = model{}
    .add_entity(drawable(rectangle(width{800}, height{600}, color::black())))
    .add_entity(drawable(rectangle(width{150}, height{75}, color::red())))
    .add_entity(drawable(line({300, 200}, {500, 400}, color::blue())));

  ctx.current_model() = m;
  emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);
}

int main() {
  run();
  return 0;
}

extern "C" {
void em_main() {
  run();
}
}
