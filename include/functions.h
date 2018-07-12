#pragma once

#include "geometry/point.h"

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
