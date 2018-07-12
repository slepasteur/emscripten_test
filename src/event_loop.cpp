#include "event_loop.h"

#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "action.h"
#include "update.h"

#include "sdl/sdl_context.h"
#include "sdl/sdl_utils.h"

namespace {

void step(sdl_context& ctx)
{
  auto actions = intents();

  for (const auto& a : actions)
  {
    ctx.current_model() = update(ctx.current_model(), a);
  }

  clear_background(color::white(), ctx.renderer());

  for (const auto& e : ctx.current_model().entities())
  {
    draw(e, ctx.renderer(), point{0, 0});
  }

  render_present(ctx.renderer());
}

#ifdef __EMSCRIPTEN__
void em_loop_handler(void *arg)
{
  sdl_context* ctx = static_cast<sdl_context*>(arg);
  step(*ctx);
}
#endif

}

void run()
{
  SDL_Init(SDL_INIT_VIDEO);
  auto ctx = sdl_context{800, 600};
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(em_loop_handler, &ctx, -1, 1);
#else
  while (!ctx.current_model().should_quit())
  {
    step(ctx);
  }
#endif
}
