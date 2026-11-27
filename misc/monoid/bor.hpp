#pragma once

namespace monoid {
  template <typename T>
  struct bor {
    static T op(const T& x, const T& y) { return x | y; }
    static T e() { return 0; }
  };
}
