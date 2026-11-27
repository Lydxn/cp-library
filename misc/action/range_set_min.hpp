#pragma once
#include <bits/stdc++.h>
#include "misc/monoid/min.hpp"

namespace action {
  template <typename T>
  struct range_set_min {
    using value_monoid = monoid::min<T>;
    using Tag = std::optional<T>;
    static Tag id() { return std::nullopt; }
    static T apply(const Tag& f, const T& val, int, int) { return f ? *f : val; }
    static Tag compose(const Tag& f, const Tag& g) { return f ? f : g; }
  };
}
