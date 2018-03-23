#pragma once

#include "sdl_window.h"

class sdl_renderer
{
public:
  sdl_renderer(sdl_window& window):
    renderer_{SDL_CreateRenderer(window.value(), -1, 0)}
  {
    if (renderer_ == nullptr)
    {
      throw std::runtime_error(SDL_GetError());
    }
  }

  sdl_renderer(const sdl_renderer&) = delete;
  sdl_renderer& operator=(const sdl_renderer&) = delete;

  sdl_renderer(sdl_renderer&& other):
    renderer_{other.renderer_}
  {
    other.renderer_ = nullptr;
  }

  sdl_renderer& operator=(sdl_renderer&& other)
  {
    std::swap(renderer_, other.renderer_);
    return *this;
  }

  ~sdl_renderer()
  {
    if (renderer_ != nullptr)
    {
      SDL_DestroyRenderer(renderer_);
    }
  }

  SDL_Renderer* value() { return renderer_; }

private:
  SDL_Renderer* renderer_;
};
