#pragma once
#include <bits/stdc++.h>

namespace monoid {
  template <typename T>
  struct gcd {
    static T op(const T& x, const T& y) { return std::gcd(x, y); }
    static T e() { return 0; }
  };
}
