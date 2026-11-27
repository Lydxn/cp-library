#pragma once
#include <bits/stdc++.h>
#include "graph/traits.hpp"

template <typename G, typename Update, typename Answer, typename To = detail::neighbor>
void dsu_on_tree(const G& g, int root, Update update, Answer answer, To to = {}) {
  int n = static_cast<int>(g.size());
  assert(0 <= root && root < n);
  std::vector<int> sz(n), heavy(n, -1);
  std::vector<int> tin(n), tout(n), euler(n);
  int timer = -1;
  auto calc_heavy = [&](this auto self, int cur, int p) -> void {
    tin[cur] = ++timer;
    euler[timer] = cur;
    sz[cur] = 1;
    for (auto&& e : adj[cur]) {
      int nxt = static_cast<int>(to(e));
      assert(0 <= nxt && nxt < n);
      if (nxt == p) continue;
      self(nxt, cur);
      sz[cur] += sz[nxt];
      if (heavy[cur] == -1 || sz[nxt] > sz[heavy[cur]])
        heavy[cur] = nxt;
    }
    tout[cur] = timer;
  };
  calc_heavy(root, -1);
  auto dfs = [&](this auto self, int cur, int p, bool keep) -> void {
    for (auto&& e : adj[cur]) {
      int nxt = static_cast<int>(to(e));
      if (nxt == p || heavy[cur] == nxt) continue;
      self(nxt, cur, false);
    }
    if (heavy[cur] != -1)
      self(heavy[cur], cur, true);
    for (auto&& e : adj[cur]) {
      int nxt = static_cast<int>(to(e));
      if (nxt == p || heavy[cur] == nxt) continue;
      for (int i = tin[nxt]; i <= tout[nxt]; i++)
        update(euler[i], 1);
    }
    update(cur, 1);
    answer(cur);
    if (!keep) {
      for (int i = tin[cur]; i <= tout[cur]; i++)
        update(euler[i], -1);
    }
  };
  dfs(root, -1, false);
}
