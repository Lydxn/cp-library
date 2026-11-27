#pragma once
#include <bits/stdc++.h>

namespace monoid {
  template <typename T, T inf = std::numeric_limits<T>::max()>
  struct min {
    static T op(const T& x, const T& y) { return std::min(x, y); }
    static T e() { return inf; }
  };
}
