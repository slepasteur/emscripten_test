#pragma once

#include <stdexcept>
#include <SDL2/SDL.h>

class sdl_window
{
public:
  sdl_window(int w, int h):
    win_{SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0)}
  {
    if (win_ == nullptr)
    {
      throw std::runtime_error(SDL_GetError());
    }
  }

  sdl_window(const sdl_window&) = delete;
  sdl_window& operator=(const sdl_window&) = delete;

  sdl_window(sdl_window&& other):
    win_{other.win_}
  {
    other.win_ = nullptr;
  }

  sdl_window& operator=(sdl_window&& other)
  {
    std::swap(win_, other.win_);
    return *this;
  }

  ~sdl_window()
  {
    if (win_ != nullptr)
    {
      SDL_DestroyWindow(win_);
    }
  }

  SDL_Window* value() { return win_; }

private:
  SDL_Window* win_;
};

