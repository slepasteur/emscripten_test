#pragma once

#include <cstdint>

struct color
{
  static constexpr color black() { return {0, 0, 0, 255}; }
  static constexpr color white() { return {255, 255, 255, 255}; }
  static constexpr color red() { return {255, 0, 0, 255}; }
  static constexpr color green() { return {0, 255, 0, 255}; }
  static constexpr color blue() { return {0, 0, 255, 255}; }

  constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    r_{r}, g_{g}, b_{b}, a_{a}
  {}

  constexpr uint8_t r() const { return r_; }
  constexpr uint8_t g() const { return g_; }
  constexpr uint8_t b() const { return b_; }
  constexpr uint8_t a() const { return a_; }

private:
  std::uint8_t r_;
  std::uint8_t g_;
  std::uint8_t b_;
  std::uint8_t a_;
};
