#pragma once
#include <bits/stdc++.h>
#include "math/modint61.hpp"

template <typename Mint = modint61>
class rolling_hash {
public:
  inline static const Mint base = std::mt19937_64(std::chrono::steady_clock::now().time_since_epoch().count())();

private:
  inline static std::vector<Mint> pw{Mint(1)};

  static void ensure(int n) {
    assert(n >= 0);
    while (int(pw.size()) <= n) pw.push_back(pw.back() * base);
  }

public:
  class sequence {
  private:
    friend class rolling_hash;
    std::vector<Mint> pre{Mint(0)};

    template <std::ranges::input_range R>
    explicit sequence(R&& range) {
      for (auto&& x : range)
        pre.push_back(pre.back() * base + (Mint(x) + Mint(1)));
      ensure(size());
    }

  public:
    int size() const { return int(pre.size()) - 1; }
    Mint get(int l, int r) const {
      assert(0 <= l && l <= r && r <= size());
      return pre[r] - pre[l] * pw[r - l];
    }
    Mint all() const { return pre.back(); }
  };

  static Mint power(int n) { ensure(n); return pw[n]; }

  template <std::ranges::input_range R>
  static sequence build(R&& range) { return sequence(std::forward<R>(range)); }

  static Mint concat(Mint lhs, Mint rhs, int rhs_len) { return rhs + lhs * power(rhs_len); }
  static Mint concat(const sequence& lhs, const sequence& rhs) {
    return concat(lhs.all(), rhs.all(), rhs.size());
  }
};
