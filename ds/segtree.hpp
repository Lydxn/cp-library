#pragma once
#include <bits/stdc++.h>

template <typename M>
class segtree {
private:
  using T = std::remove_cvref_t<decltype(M::e())>;
  int n = 0, sz = 1;
  std::vector<T> data;

  void init(int n_) {
    assert(n_ >= 0);
    n = n_, sz = 1;
    while (sz < n) sz <<= 1;
    data.assign(2 * sz, M::e());
  }

  void build() {
    for (int i = sz - 1; i > 0; i--)
      data[i] = M::op(data[i << 1], data[i << 1 | 1]);
  }

public:
  segtree() = default;
  explicit segtree(int n_, const T& val = M::e()) {
    init(n_);
    std::fill(data.begin() + sz, data.begin() + sz + n, val);
    build();
  }
  template <std::ranges::sized_range R>
  explicit segtree(R&& r) {
    init(int(std::ranges::size(r)));
    std::ranges::copy(r, data.begin() + sz);
    build();
  }
  template <typename G>
  requires std::invocable<G&, int>
  explicit segtree(int n_, G gen) {
    init(n_);
    for (int i = 0; i < n; i++) data[sz + i] = std::invoke(gen, i);
    build();
  }

  void set(int i, T val) {
    assert(0 <= i && i < n);
    data[i += sz] = std::move(val);
    while (i >>= 1) data[i] = M::op(data[i << 1], data[i << 1 | 1]);
  }

  void apply(int i, const T& val) {
    assert(0 <= i && i < n);
    set(i, M::op(data[i + sz], val));
  }

  T prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    T lhs = M::e(), rhs = M::e();
    for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lhs = M::op(lhs, data[l++]);
      if (r & 1) rhs = M::op(data[--r], rhs);
    }
    return M::op(lhs, rhs);
  }

  T prod_all() const { return n ? data[1] : M::e(); }
  int size() const { return n; }

  const T& operator[](int i) const {
    assert(0 <= i && i < n);
    return data[i + sz];
  }

  template <typename P>
  int max_right(int l, P pred) const {
    assert(0 <= l && l <= n && pred(M::e()));
    if (l == n) return n;
    l += sz;
    T val = M::e();
    do {
      while ((l & 1) == 0) l >>= 1;
      if (!pred(M::op(val, data[l]))) {
        while (l < sz) {
          l <<= 1;
          if (pred(M::op(val, data[l])))
            val = M::op(val, data[l++]);
        }
        return l - sz;
      }
      val = M::op(val, data[l++]);
    } while ((l & -l) != l);
    return n;
  }

  template <typename P>
  int min_left(int r, P pred) const {
    assert(0 <= r && r <= n && pred(M::e()));
    if (r == 0) return 0;
    r += sz;
    T val = M::e();
    do {
      r--;
      while (r > 1 && (r & 1) == 1) r >>= 1;
      if (!pred(M::op(data[r], val))) {
        while (r < sz) {
          r = r << 1 | 1;
          if (pred(M::op(data[r], val)))
            val = M::op(data[r--], val);
        }
        return r + 1 - sz;
      }
      val = M::op(data[r], val);
    } while ((r & -r) != r);
    return 0;
  }
};
