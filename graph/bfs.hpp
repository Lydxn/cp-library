#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <
  typename G,
  std::ranges::input_range Sources,
  typename To = detail::neighbor
>
auto bfs(const G& g, Sources&& sources, To to = {}) {
  int n = static_cast<int>(g.size());
  std::vector<int> dst(n, std::numeric_limits<int>::max());
  std::vector<int> par(n, -1);
  std::queue<int> q;
  for (auto&& src_ : sources) {
    int src = static_cast<int>(src_);
    assert(0 <= src && src < n);
    if (dst[src] == std::numeric_limits<int>::max()) {
      dst[src] = 0;
      q.push(src);
    }
  }
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto&& e : g[u]) {
      int v = static_cast<int>(to(e));
      assert(0 <= v && v < n);
      if (dst[u] + 1 < dst[v]) {
        dst[v] = dst[u] + 1;
        par[v] = u;
        q.push(v);
      }
    }
  }
  return std::pair{std::move(dst), std::move(par)};
}

template <typename G, typename To = detail::neighbor>
auto bfs(const G& g, int start, To to = {}) {
  return bfs(g, std::views::single(start), std::move(to));
}
