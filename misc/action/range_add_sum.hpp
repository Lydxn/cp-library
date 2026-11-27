#pragma once
#include "misc/monoid/add.hpp"

namespace action {
  template <typename T>
  struct range_add_sum {
    using value_monoid = monoid::add<T>;
    static T id() { return 0; }
    static T apply(const T& f, const T& val, int l, int r) { return val + f * (r - l); }
    static T compose(const T& f, const T& g) { return f + g; }
  };
}
