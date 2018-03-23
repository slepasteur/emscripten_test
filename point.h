#pragma once

struct point
{
  constexpr point(int x, int y):
    x_{x}, y_{y}
  {}

  constexpr int x() const { return x_; }
  constexpr int y() const { return y_; }

private:
  int x_;
  int y_;
};
