#pragma once
#include <bits/stdc++.h>

template <typename G>
class potential_union_find {
private:
  using T = std::remove_cvref_t<decltype(G::e())>;
  int cnt = 0;
  std::vector<int> data;
  std::vector<T> pot;

public:
  potential_union_find() = default;
  explicit potential_union_find(int n)
    : cnt(n), data(n, -1), pot(n, G::e()) {}

  int find(int u) {
    assert(0 <= u && u < int(data.size()));
    int p = data[u];
    if (p < 0) return u;
    int root = find(p);
    pot[u] = G::op(pot[p], pot[u]);
    return data[u] = root;
  }

  T potential(int u) {
    find(u);
    return pot[u];
  }

  T diff(int u, int v) {
    int ru = find(u), rv = find(v);
    assert(ru == rv);
    return G::op(G::inv(pot[u]), pot[v]);
  }

  bool unite(int u, int v, const T& w) {
    int ru = find(u), rv = find(v);
    if (ru == rv) {
      assert(G::op(G::inv(pot[u]), pot[v]) == w);
      return false;
    }
    T d = G::op(G::op(pot[u], w), G::inv(pot[v]));
    if (data[ru] > data[rv]) {
      std::swap(ru, rv);
      d = G::inv(d);
    }
    data[ru] += data[rv];
    data[rv] = ru;
    pot[rv] = std::move(d);
    --cnt;
    return true;
  }

  bool same(int u, int v) { return find(u) == find(v); }
  int size(int u) { return -data[find(u)]; }
  int count() { return cnt; }
};
