#pragma once

#include <vector>

#include "model.h"
#include "sdl_renderer.h"

class sdl_context
{
public:
  sdl_context(int w, int h):
    window_{w, h},
    renderer_{window_}
  {}

  sdl_context(const sdl_context&) = delete;
  sdl_context& operator=(const sdl_context&) = delete;
  sdl_context(sdl_context&&) = default;
  sdl_context& operator=(sdl_context&&) = default;

  sdl_renderer& renderer() { return renderer_; }
  const sdl_renderer& renderer() const { return renderer_; }

  model& current_model() { return model_; }

private:
  sdl_context(sdl_window window, sdl_renderer renderer):
    window_{std::move(window)},
    renderer_{std::move(renderer)}
  {}

  sdl_window window_;
  sdl_renderer renderer_;
  model model_;
};
