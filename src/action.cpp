#include "action.h"

#include <SDL2/SDL.h>

std::optional<action> intent(const SDL_Event& event)
{
  switch (event.type) {
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          return {up{}};
        case SDLK_DOWN:
          return {down{}};
        case SDLK_LEFT:
          return {left{}};
        case SDLK_RIGHT:
          return {right{}};
      }
      break;
  }

  return std::nullopt;
}

std::vector<action> intents()
{
  SDL_Event event;
  std::vector<action> result;

  while (SDL_PollEvent(&event)) {
    auto i = intent(event);
    if (i)
    {
      result.push_back(std::move(*i));
    }
  }

  return result;
}

