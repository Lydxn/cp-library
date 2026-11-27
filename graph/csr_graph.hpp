#pragma once
#include <bits/stdc++.h>
#include "graph/edge.hpp"

template <typename T = void, bool is_directed = false>
class csr_graph {
public:
  using edge = detail::graph_edge<T, int>;

private:
  int n = 0;
  std::vector<int> adj, pos;
  std::vector<edge> edges_;
  bool built = false;

  int insert(edge e) {
    assert(0 <= e.from && e.from < n);
    assert(0 <= e.to && e.to < n);
    int id = static_cast<int>(edges_.size());
    edges_.push_back(std::move(e));
    built = false;
    return id;
  }

public:
  csr_graph() = default;
  explicit csr_graph(int n_) : n(n_) { assert(n >= 0); }

  int add(int u, int v) {
    if constexpr (std::is_void_v<T>) {
      return insert({u, v});
    } else {
      return insert({u, v, T(1)});
    }
  }

  template <typename U>
  requires(!std::is_void_v<T>)
  int add(int u, int v, U&& val) {
    return insert({u, v, T(std::forward<U>(val))});
  }

  void build() {
    pos.assign(n + 1, 0);
    for (const auto& e : edges_) {
      pos[e.from + 1]++;
      if constexpr (!is_directed)
        pos[e.to + 1]++;
    }
    for (int i = 1; i <= n; i++) pos[i] += pos[i - 1];
    adj.resize(pos[n]);
    auto cnt = pos;
    int m = static_cast<int>(edges_.size());
    for (int id = 0; id < m; id++) {
      const auto& e = edges_[id];
      adj[cnt[e.from]++] = id;
      if constexpr (!is_directed)
        adj[cnt[e.to]++] = id;
    }
    built = true;
  }

  std::span<const int> edge_ids(int u) const {
    assert(built);
    assert(0 <= u && u < n);
    return std::span<const int>(adj.begin() + pos[u], adj.begin() + pos[u + 1]);
  }

  auto operator[](int u) const {
    return edge_ids(u) | std::views::transform([this, u](int id) {
      const auto& e = edges_[id];
      int v = e.to;
      if constexpr (!is_directed)
        v = u ^ e.from ^ e.to;
      if constexpr (std::is_void_v<T>) {
        return v;
      } else {
        return std::make_pair(v, e.val);
      }
    });
  }

  int deg(int u) const {
    assert(built);
    assert(0 <= u && u < n);
    return pos[u + 1] - pos[u];
  }
  const std::vector<edge>& edges() const { return edges_; }
  int size() const { return n; }
};

template <typename T = void>
using csr_digraph = csr_graph<T, true>;
