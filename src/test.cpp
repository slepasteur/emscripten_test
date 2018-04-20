#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <variant>

#include "rectangle.h"
#include "line.h"
#include "sdl_context.h"
#include "sdl_utils.h"
#include "action.h"





template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  auto actions = intents();

  for (const auto& a : actions)
  {
    std::visit(overloaded {
        [](up){ std::cout << "up\n"; },
        [](down){ std::cout << "down\n"; },
        [](left){ std::cout << "left\n"; },
        [](right){ std::cout << "right\n"; },
        }, a);
  }

  clear_background(color::white(), ctx->renderer());

  for (const auto& e : ctx->entities())
  {
    draw(e, ctx->renderer());
  }

  render_present(ctx->renderer());
}

void run()
{
  SDL_Init(SDL_INIT_VIDEO);

  auto ctx = sdl_context{800, 600}
    .add_entity(drawable(rectangle({0, 0}, 800, 600, color::black())))
    .add_entity(drawable(rectangle({50, 50}, 150, 75, color::red())))
    .add_entity(drawable(line({300, 200}, {500, 400}, color::blue())));

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
