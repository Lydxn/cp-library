#pragma once

namespace monoid {
  template <typename T>
  struct add {
    static T op(const T& x, const T& y) { return x + y; }
    static T e() { return 0; }
    static T inv(const T& x) { return -x; }
  };
}
