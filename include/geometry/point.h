#pragma once

struct point
{
  constexpr point() :
    point{0, 0}
  {}
  constexpr point(int x, int y):
    x_{x}, y_{y}
  {}

  constexpr int x() const { return x_; }
  constexpr int y() const { return y_; }

private:
  int x_;
  int y_;
};

inline point operator+(const point& lhs, const point& rhs)
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

inline point operator-(const point& lhs, const point& rhs)
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

inline bool operator==(const point& lhs, const point& rhs)
{
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline bool operator!=(const point& lhs, const point& rhs)
{
  return !(lhs == rhs);
}
