#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <variant>

#include "rectangle.h"
#include "line.h"
#include "sdl_context.h"
#include "sdl_utils.h"


struct up{};
struct down{};
struct left{};
struct right{};

using input_event = std::variant<up, down, left, right>;

std::vector<input_event> process_input()
{
  SDL_Event event;
  std::vector<input_event> result;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            result.push_back(up{});
            break;
          case SDLK_DOWN:
            result.push_back(down{});
            break;
          case SDLK_LEFT:
            result.push_back(left{});
            break;
          case SDLK_RIGHT:
            result.push_back(right{});
            break;
        }
        break;
    }
  }

  return result;
}


template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  auto events = process_input();

  for (const auto& e : events)
  {
    std::visit(overloaded {
        [](up){ std::cout << "up\n"; },
        [](down){ std::cout << "down\n"; },
        [](left){ std::cout << "left\n"; },
        [](right){ std::cout << "right\n"; },
        }, e);
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
