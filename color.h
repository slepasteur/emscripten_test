#pragma once

struct color
{
  static constexpr color black() { return {0, 0, 0, 255}; }
  static constexpr color white() { return {255, 255, 255, 255}; }
  static constexpr color red() { return {255, 0, 0, 255}; }
  static constexpr color green() { return {0, 255, 0, 255}; }
  static constexpr color blue() { return {0, 0, 255, 255}; }

  constexpr color(int r, int g, int b, int a):
    r_{r}, g_{g}, b_{b}, a_{a}
  {}

  constexpr int r() const { return r_; }
  constexpr int g() const { return g_; }
  constexpr int b() const { return b_; }
  constexpr int a() const { return a_; }

private:
  int r_;
  int g_;
  int b_;
  int a_;
};
