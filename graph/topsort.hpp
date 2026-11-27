#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <typename G, typename To = detail::neighbor>
auto topsort(G&& g, int first = 0, To to = {}) {
  int n = static_cast<int>(g.size());
  std::vector<int> indeg(n);
  for (int i = first; i < n; i++) {
    for (auto&& e : g[i]) {
      int v = static_cast<int>(to(e));
      assert(first <= v && v < n);
      ++indeg[v];
    }
  }
  std::vector<int> order;
  for (int i = first; i < n; i++) {
    if (!indeg[i]) order.push_back(i);
  }
  for (size_t i = 0; i < order.size(); i++) {
    for (auto&& e : g[order[i]]) {
      int v = static_cast<int>(to(e));
      assert(first <= v && v < n);
      if (!--indeg[v]) order.push_back(v);
    }
  }
  return order;
}
