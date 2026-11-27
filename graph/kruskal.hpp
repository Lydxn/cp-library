#pragma once
#include <bits/stdc++.h>
#include "ds/union_find.hpp"

template <typename Cost = void, typename E, typename Proj = std::identity>
auto kruskal(const E& edges, int first, int last, Proj proj = {}) {
  auto weight = [&](int id) {
    const auto& [u, v, w] = proj(edges[id]);
    return w;
  };
  using T = std::conditional_t<std::is_void_v<Cost>, decltype(weight(0)), Cost>;
  assert(0 <= first && first <= last);
  std::vector<int> ids(edges.size());
  std::iota(ids.begin(), ids.end(), 0);
  std::ranges::sort(ids, {}, weight);
  union_find uf(last + 1);
  int need = last - first;
  std::vector<int> used;
  used.reserve(need);
  T cost{};
  for (int id : ids) {
    const auto& [u, v, w] = proj(edges[id]);
    assert(first <= u && u <= last);
    assert(first <= v && v <= last);
    if (uf.unite(u, v)) {
      cost += w;
      used.push_back(id);
      if (int(used.size()) == need)
        break;
    }
  }
  return std::pair{cost, std::move(used)};
}
