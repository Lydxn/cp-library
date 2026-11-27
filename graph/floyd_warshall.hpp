#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <
  typename Cost = void,
  typename G,
  typename To = detail::neighbor,
  typename Weight = detail::weight
>
auto floyd_warshall(const G& g, Weight weight = {}, To to = {}) {
  using Edge = std::ranges::range_reference_t<decltype(g[0])>;
  using W = std::remove_cvref_t<std::invoke_result_t<Weight&, Edge>>;
  using T = std::conditional_t<std::is_void_v<Cost>, W, Cost>;
  int n = static_cast<int>(g.size());
  const T inf = std::numeric_limits<T>::max();
  std::vector<std::vector<T>> dst(n, std::vector<T>(n, inf));
  for (int u = 0; u < n; u++) {
    dst[u][u] = 0;
    for (auto&& e : g[u]) {
      int v = static_cast<int>(to(e));
      T w = static_cast<T>(weight(e));
      assert(0 <= v && v < n);
      dst[u][v] = std::min(dst[u][v], w);
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (dst[i][k] == inf) continue;
      for (int j = 0; j < n; j++) {
        if (dst[k][j] == inf) continue;
        dst[i][j] = std::min(dst[i][j], dst[i][k] + dst[k][j]);
      }
    }
  }
  return dst;
}
