#pragma once
#include <bits/stdc++.h>

namespace monoid {
  template <typename T, T neg_inf = std::numeric_limits<T>::lowest()>
  struct max {
    static T op(const T& x, const T& y) { return std::max(x, y); }
    static T e() { return neg_inf; }
  };
}
