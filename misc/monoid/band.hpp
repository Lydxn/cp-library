#pragma once

namespace monoid {
  template <typename T>
  struct band {
    static T op(const T& x, const T& y) { return x & y; }
    static T e() { return ~T(0); }
  };
}
