#include <iostream>
#include <SDL2/SDL.h>
#include <emscripten.h>
#include <variant>
#include <tuple>

#include "draw/rectangle.h"
#include "draw/line.h"
#include "sdl/sdl_context.h"
#include "sdl/sdl_utils.h"
#include "action.h"

#include "overloaded.h"

constexpr auto orig = point{0,0};
point pos;

template <typename F>
auto on_selected(F&& f)
{
  return [f = std::forward<F>(f)](const auto& e) {
    return e.selected() ? f(e) : e;
  };
}

template <typename F>
auto on_colliding(point p, F&& f)
{
  return [f = std::forward<F>(f), p = std::move(p)](const auto& e) {
    return is_within(p, e.bbox()) ? f(e) : e;
  };
}

/**
 * Combine multiple functions to be applied on entities together.
 */
template <typename... Fs>
auto all(Fs... fs)
{
  // Capture fs into a tuple, "accumulate" the result of each invocation of fs into e and finally
  // return the "accumulated" value (i.e. return value of the last function).
  return [fs = std::make_tuple(std::forward<Fs>(fs) ...)](const auto& e) {
    return std::apply(
      [&e](auto&& ... fs) {
        auto updated_entity = e;
        ((updated_entity = fs(updated_entity)), ...);
        return updated_entity;
      },
      std::move(fs)
    );
  };
}

model update(model m, action a)
{
  return std::visit(overloaded {
      [&] (up) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{0, -1}); } )
        );
      },
      [&] (down) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{0, 1}); } )
        );
      },
      [&] (left) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{-1, 0}); } )
        );
      },
      [&] (right) {
        return m.update_entities(
          on_selected( [](const auto& e){ return e.move(point{1, 0}); } )
        );
      },
      [&] (selection s) { 
        return m.update_entities(
          all(
            on_selected( [](const auto& e){ return e.deselect(); } ),
            on_colliding( s.coordinates_, [](const auto& e){ return e.select(); } )
          )
        );
      }
  }, a);
}

void loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);

  auto actions = intents();

  for (const auto& a : actions)
  {
    ctx->current_model() = update(ctx->current_model(), a);
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
    .add_entity(entity{drawable(rectangle(width{800}, height{600}, color::black())), orig})
    .add_entity(
        entity{drawable(rectangle(width{150}, height{75}, color::red())), orig}
        .with_bbox(bounding_box{point{0, 0}, width{150}, height{75}})
    )
    .add_entity(entity{drawable(line({300, 200}, {500, 400}, color::blue())), orig});

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
