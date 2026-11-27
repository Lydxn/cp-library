#pragma once
#include <bits/stdc++.h>

template <typename A>
class lazy_segtree {
private:
  using M = typename A::value_monoid;
  using T = std::remove_cvref_t<decltype(M::e())>;
  using Tag = std::remove_cvref_t<decltype(A::id())>;

  int n = 0, sz = 1;
  std::vector<T> data;
  std::vector<Tag> lazy;

  void init(int n_) {
    assert(n_ >= 0);
    n = n_, sz = 1;
    while (sz < n) sz <<= 1;
    data.assign(2 * sz, M::e());
    lazy.assign(2 * sz, A::id());
  }

  void build() {
    for (int i = sz - 1; i > 0; i--)
      data[i] = M::op(data[i << 1], data[i << 1 | 1]);
  }

  void apply_node(int u, const Tag& tag, int l, int r) {
    data[u] = A::apply(tag, data[u], l, r);
    lazy[u] = A::compose(tag, lazy[u]);
  }

  void push(int u, int l, int r) {
    int mid = (l + r) / 2;
    apply_node(u << 1, lazy[u], l, mid);
    apply_node(u << 1 | 1, lazy[u], mid, r);
    lazy[u] = A::id();
  }

  void set(int u, int l, int r, int idx, T val) {
    if (l + 1 == r) {
      data[u] = std::move(val);
      lazy[u] = A::id();
      return;
    }
    push(u, l, r);
    int mid = (l + r) / 2;
    if (idx < mid)
      set(u << 1, l, mid, idx, std::move(val));
    else
      set(u << 1 | 1, mid, r, idx, std::move(val));
    data[u] = M::op(data[u << 1], data[u << 1 | 1]);
  }

  void apply(int u, int l, int r, int ql, int qr, const Tag& tag) {
    if (l >= qr || r <= ql) return;
    if (ql <= l && r <= qr) {
      apply_node(u, tag, l, r);
      return;
    }
    push(u, l, r);
    int mid = (l + r) / 2;
    apply(u << 1, l, mid, ql, qr, tag);
    apply(u << 1 | 1, mid, r, ql, qr, tag);
    data[u] = M::op(data[u << 1], data[u << 1 | 1]);
  }

  T prod(int u, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) return M::e();
    if (ql <= l && r <= qr) return data[u];
    push(u, l, r);
    int mid = (l + r) / 2;
    return M::op(prod(u << 1, l, mid, ql, qr), prod(u << 1 | 1, mid, r, ql, qr));
  }

  template <typename P>
  int max_right(int u, int l, int r, T& acc, int ql, P& pred) {
    if (r <= ql) return r;
    if (ql <= l) {
      T next = M::op(acc, data[u]);
      if (pred(next)) {
        acc = std::move(next);
        return r;
      }
      if (r - l == 1) return l;
    }
    push(u, l, r);
    int mid = (l + r) / 2;
    int result = max_right(u << 1, l, mid, acc, ql, pred);
    return result < mid ? result : max_right(u << 1 | 1, mid, r, acc, ql, pred);
  }

  template <typename P>
  int min_left(int u, int l, int r, T& acc, int qr, P& pred) {
    if (qr <= l) return l;
    if (r <= qr) {
      T next = M::op(data[u], acc);
      if (pred(next)) {
        acc = std::move(next);
        return l;
      }
      if (r - l == 1) return r;
    }
    push(u, l, r);
    int mid = (l + r) / 2;
    int result = min_left(u << 1 | 1, mid, r, acc, qr, pred);
    return result > mid ? result : min_left(u << 1, l, mid, acc, qr, pred);
  }

public:
  lazy_segtree() = default;
  explicit lazy_segtree(int n_, const T& val = M::e()) {
    init(n_);
    std::fill(data.begin() + sz, data.begin() + sz + n, val);
    build();
  }
  template <std::ranges::sized_range R>
  explicit lazy_segtree(R&& r) {
    init(int(std::ranges::size(r)));
    std::ranges::copy(r, data.begin() + sz);
    build();
  }
  template <typename G>
  requires std::invocable<G&, int>
  explicit lazy_segtree(int n_, G gen) {
    init(n_);
    for (int i = 0; i < n; i++) data[i + sz] = std::invoke(gen, i);
    build();
  }

  void set(int i, T val) {
    assert(0 <= i && i < n);
    set(1, 0, sz, i, std::move(val));
  }

  void apply(int l, int r, const Tag& tag) {
    assert(0 <= l && l <= r && r <= n);
    apply(1, 0, sz, l, r, tag);
  }

  void apply(int i, const Tag& tag) {
    apply(i, i + 1, tag);
  }

  T prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return prod(1, 0, sz, l, r);
  }

  T prod_all() const { return n ? data[1] : M::e(); }
  int size() const { return n; }

  template <typename P>
  int max_right(int l, P pred) {
    assert(0 <= l && l <= n && pred(M::e()));
    T acc = M::e();
    return std::min(n, max_right(1, 0, sz, acc, l, pred));
  }

  template <typename P>
  int min_left(int r, P pred) {
    assert(0 <= r && r <= n && pred(M::e()));
    T acc = M::e();
    return min_left(1, 0, sz, acc, r, pred);
  }
};
