#pragma once

#include "sdl_renderer.h"

class sdl_context
{
public:
  sdl_context(int w, int h):
    window_{w, h},
    renderer_{window_}
  {}

  sdl_renderer& renderer() { return renderer_; }
  const sdl_renderer& renderer() const { return renderer_; }

private:
  sdl_window window_;
  sdl_renderer renderer_;
};
