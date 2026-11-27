#pragma once
#include <bits/stdc++.h>
#include "misc/monoid/add.hpp"

template <typename M>
class fenwick_generic {
private:
  using T = std::remove_cvref_t<decltype(M::e())>;
  int n = 0;
  std::vector<T> data;

  void build() {
    n = int(data.size());
    for (int i = 0; i < n; i++) {
      int j = i | (i + 1);
      if (j < n) data[j] = M::op(data[j], data[i]);
    }
  }

public:
  fenwick_generic() = default;
  explicit fenwick_generic(int n_, const T& val = M::e()) {
    assert(n_ >= 0);
    data.assign(n_, val);
    build();
  }
  template <std::ranges::input_range R>
  explicit fenwick_generic(R&& r) {
    std::ranges::copy(r, std::back_inserter(data));
    build();
  }
  template <typename G>
  requires std::invocable<G&, int>
  explicit fenwick_generic(int n_, G gen) {
    assert(n_ >= 0);
    data.reserve(n_);
    for (int i = 0; i < n_; i++) data.push_back(std::invoke(gen, i));
    build();
  }

  void add(int i, const T& val) {
    assert(0 <= i && i < n);
    for (; i < n; i |= i + 1) data[i] = M::op(data[i], val);
  }

  T sum(int i) const {
    assert(0 <= i && i <= n);
    T ret = M::e();
    for (; i > 0; i &= i - 1) ret = M::op(ret, data[i - 1]);
    return ret;
  }

  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return M::op(sum(r), M::inv(sum(l)));
  }

  int size() const { return n; }

  template <typename P>
  int max_right(P pred) const {
    assert(pred(M::e()));
    int r = 0;
    T val = M::e();
    for (int k = std::bit_floor<unsigned>(n); k > 0; k >>= 1) {
      int nr = r + k;
      if (nr <= n) {
        T next = M::op(val, data[nr - 1]);
        if (pred(next)) {
          r = nr;
          val = std::move(next);
        }
      }
    }
    return r;
  }
};

template <typename T>
using fenwick = fenwick_generic<monoid::add<T>>;
