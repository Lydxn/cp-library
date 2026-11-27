#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <typename G, typename To = detail::neighbor>
auto kosaraju(const G& g, int first = 0, To to = {}) {
  int n = static_cast<int>(g.size());
  std::vector<bool> vis(n);
  std::vector<int> ord;
  std::vector<std::vector<int>> rg(n);
  ord.reserve(n - first);
  auto dfs = [&](this auto self, int v) -> void {
    vis[v] = true;
    for (auto&& e : g[v]) {
      int nxt = static_cast<int>(to(e));
      assert(first <= nxt && nxt < n);
      rg[nxt].push_back(v);
      if (!vis[nxt]) self(nxt);
    }
    ord.push_back(v);
  };
  for (int v = first; v < n; v++) {
    if (!vis[v]) dfs(v);
  }
  std::vector<int> comp(n, -1);
  int count = 0;
  auto rdfs = [&](this auto self, int v) -> void {
    comp[v] = count;
    for (int nxt : rg[v]) {
      if (comp[nxt] == -1) self(nxt);
    }
  };
  for (int i = static_cast<int>(ord.size()) - 1; i >= 0; i--) {
    if (comp[ord[i]] == -1) {
      rdfs(ord[i]);
      ++count;
    }
  }
  return std::pair{count, std::move(comp)};
}
