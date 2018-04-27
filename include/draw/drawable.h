#pragma once

#include <memory>

#include "draw/rectangle.h"
#include "sdl/sdl_renderer.h"

class drawable
{
public:
  template <typename T>
  explicit drawable(T x):
    self_{std::make_shared<drawable_model<T>>(std::move(x))}
  {}

  friend void draw(const drawable& e, sdl_renderer& renderer)
  {
    e.self_->draw_(renderer);
  }

private:
  struct drawable_concept
  {
    virtual ~drawable_concept();
    virtual void draw_(sdl_renderer& renderer) const = 0;
  };

  template <typename T>
  struct drawable_model final: drawable_concept
  {
    drawable_model(T x):
      data_{std::move(x)}
    {}

    void draw_(sdl_renderer& renderer) const override
    {
      draw(data_, renderer);
    }

    T data_;
  };

  std::shared_ptr<const drawable_concept> self_;
};
