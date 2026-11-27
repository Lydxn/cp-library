#pragma once
#include <bits/stdc++.h>
#include "misc/monoid/add.hpp"

namespace action {
  template <typename T>
  struct range_set_sum {
    using value_monoid = monoid::add<T>;
    using Tag = std::optional<T>;
    static Tag id() { return std::nullopt; }
    static T apply(const Tag& f, const T& val, int l, int r) { return f ? *f * (r - l) : val; }
    static Tag compose(const Tag& f, const Tag& g) { return f ? f : g; }
  };
}
