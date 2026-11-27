#pragma once
#include <bits/stdc++.h>

struct node {
  T sum{}, pre{}, suf{}, best{};
  bool empty = true;
  node() = default;
  node(const T& x) : sum(x), pre(x), suf(x), best(x), empty(false) {}
};

namespace monoid {
  template <typename T>
  struct max_sum_subarray {
    static node op(const node& lhs, const node& rhs) {
      if (lhs.empty) return rhs;
      if (rhs.empty) return lhs;
      node res;
      res.sum = lhs.sum + rhs.sum;
      res.pre = std::max(lhs.pre, lhs.sum + rhs.pre);
      res.suf = std::max(rhs.suf, rhs.sum + lhs.suf);
      res.best = std::max({lhs.best, rhs.best, lhs.suf + rhs.pre});
      res.empty = false;
      return res;
    }
    static node e() { return {}; }
  };
}
