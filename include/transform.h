#pragma once

#include <immer/vector.hpp>
#include <immer/vector_transient.hpp>
#include <immer/algorithm.hpp>

template <typename T, typename F>
immer::vector<T> transform(immer::vector<T> v, F f)
{
  immer::vector_transient<T> t;
  immer::for_each(v, [&](auto&& x){ t.push_back(f(x)); });
  return t.persistent();
}

template <typename T, typename P, typename F>
immer::vector<T> transform(immer::vector<T> v, P predicate, F func)
{
  auto t = v.transient();

  for (size_t i = 0; i < v.size(); ++i)
  {
    if (predicate(t[i]))
    {
      t = std::move(t).update(i, func);
    }
  }

  return t.persistent();
}


