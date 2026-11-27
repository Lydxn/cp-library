#pragma once
#include "misc/monoid/max.hpp"

namespace action {
  template <typename T>
  struct range_add_max {
    using value_monoid = monoid::max<T>;
    static T id() { return 0; }
    static T apply(const T& f, const T& val, int, int) { return val + f; }
    static T compose(const T& f, const T& g) { return f + g; }
  };
}
