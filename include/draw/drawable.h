#pragma once

#include <memory>

#include "draw/rectangle.h"
#include "sdl/sdl_renderer.h"

template <typename T>
inline void draw(const T& t, sdl_renderer& renderer, const point& pos)
{
  t.draw(renderer, pos);
}

class drawable
{
public:
  template <typename T>
  explicit drawable(T x):
    self_{std::make_shared<drawable_model<T>>(std::move(x))}
  {}

  void draw(sdl_renderer& renderer, const point& pos) const
  {
    self_->draw_(renderer, pos);
  }

private:
  struct drawable_concept
  {
    virtual ~drawable_concept();
    virtual void draw_(sdl_renderer& renderer, const point& pos) const = 0;
  };

  template <typename T>
  struct drawable_model final: drawable_concept
  {
    drawable_model(T x):
      data_{std::move(x)}
    {}

    void draw_(sdl_renderer& renderer, const point& pos) const override
    {
      ::draw(data_, renderer, pos);
    }

    T data_;
  };

  std::shared_ptr<const drawable_concept> self_;
};


