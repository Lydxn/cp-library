#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <
  typename Cost = void,
  typename G,
  std::ranges::input_range Sources,
  typename To = detail::neighbor,
  typename Weight = detail::weight
>
auto bellman_ford(const G& g, Sources&& sources, Weight weight = {}, To to = {}) {
  using Edge = std::ranges::range_reference_t<decltype(g[0])>;
  using W = std::remove_cvref_t<std::invoke_result_t<Weight&, Edge>>;
  using T = std::conditional_t<std::is_void_v<Cost>, W, Cost>;
  static_assert(std::numeric_limits<T>::is_signed);
  int n = static_cast<int>(g.size());
  std::vector<T> dst(n, std::numeric_limits<T>::max());
  std::vector<int> par(n, -1);
  std::vector<bool> neg(n);
  std::queue<int> q;
  for (auto&& src_ : sources) {
    int src = static_cast<int>(src_);
    assert(0 <= src && src < n);
    dst[src] = T{};
  }
  for (int it = 0; it < n; it++) {
    bool changed = false;
    for (int u = 0; u < n; u++) {
      if (dst[u] == std::numeric_limits<T>::max()) continue;
      for (auto&& e : g[u]) {
        int v = static_cast<int>(to(e));
        assert(0 <= v && v < n);
        T w = static_cast<T>(weight(e));
        T nd = dst[u] + w;
        if (nd < dst[v]) {
          dst[v] = nd;
          par[v] = u;
          changed = true;
          if (it == n - 1 && !neg[v]) {
            neg[v] = true;
            par[v] = u;
            q.push(v);
          }
        }
      }
    }
    if (!changed) break;
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    dst[u] = std::numeric_limits<T>::lowest();
    for (auto&& e : g[u]) {
      int v = static_cast<int>(to(e));
      if (!neg[v]) {
        neg[v] = true;
        q.push(v);
      }
    }
  }
  return std::pair{std::move(dst), std::move(par)};
}

template <
  typename Cost = void,
  typename G,
  typename To = detail::neighbor,
  typename Weight = detail::weight
>
auto bellman_ford(const G& g, int start, Weight weight = {}, To to = {}) {
  return bellman_ford<Cost>(g, std::views::single(start), std::move(weight), std::move(to));
}
