#pragma once

#include <vector>

#include "drawable.h"
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

  const std::vector<drawable>& entities() const { return entities_; }

  sdl_context add_entity(drawable e) &&
  {
    entities_.push_back(std::move(e));
    return sdl_context{
      std::move(window_),
      std::move(renderer_),
      std::move(entities_)
    };
  }

private:
  sdl_context(sdl_window window, sdl_renderer renderer, std::vector<drawable> entities):
    window_{std::move(window)},
    renderer_{std::move(renderer)},
    entities_{std::move(entities)}
  {}

  sdl_window window_;
  sdl_renderer renderer_;

  std::vector<drawable> entities_;
};
