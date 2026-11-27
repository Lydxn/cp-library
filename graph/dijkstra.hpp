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
auto dijkstra(const G& g, Sources&& sources, Weight weight = {}, To to = {}) {
  using Edge = std::ranges::range_reference_t<decltype(g[0])>;
  using W = std::remove_cvref_t<std::invoke_result_t<Weight&, Edge>>;
  using T = std::conditional_t<std::is_void_v<Cost>, W, Cost>;
  int n = static_cast<int>(g.size());
  std::vector<T> dst(n, std::numeric_limits<T>::max());
  std::vector<int> par(n, -1);
  using P = std::pair<T, int>;
  std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
  for (auto&& src_ : sources) {
    int src = static_cast<int>(src_);
    assert(0 <= src && src < n);
    if (dst[src] == std::numeric_limits<T>::max()) {
      dst[src] = T{};
      pq.emplace(T{}, src);
    }
  }
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dst[u]) continue;
    for (auto&& e : g[u]) {
      int v = static_cast<int>(to(e));
      T w = static_cast<T>(weight(e));
      assert(0 <= v && v < n);
      assert(T{} <= w && w <= std::numeric_limits<T>::max() - d);
      T nd = d + w;
      if (nd < dst[v]) {
        dst[v] = nd;
        par[v] = u;
        pq.emplace(nd, v);
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
auto dijkstra(const G& g, int start, Weight weight = {}, To to = {}) {
  return dijkstra<Cost>(g, std::views::single(start), std::move(weight), std::move(to));
}
