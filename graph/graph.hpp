#pragma once
#include <bits/stdc++.h>
#include "graph/edge.hpp"

template <typename T = void, bool is_directed = false>
class graph {
public:
  using edge = detail::graph_edge<T, int>;

private:
  std::vector<std::vector<int>> adj;
  std::vector<edge> edges_;

  int insert(edge e) {
    assert(0 <= e.from && e.from < int(adj.size()));
    assert(0 <= e.to && e.to < int(adj.size()));
    int id = static_cast<int>(edges_.size());
    int u = e.from, v = e.to;
    edges_.push_back(std::move(e));
    adj[u].push_back(id);
    if constexpr (!is_directed)
      adj[v].push_back(id);
    return id;
  }

public:
  graph() = default;
  explicit graph(int n) {
    assert(n >= 0);
    adj.resize(n);
  }

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

  std::span<const int> edge_ids(int u) const {
    assert(0 <= u && u < int(adj.size()));
    return std::span<const int>(adj[u]);
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
    assert(0 <= u && u < int(adj.size()));
    return static_cast<int>(adj[u].size());
  }
  const std::vector<edge>& edges() const { return edges_; }
  int size() const { return static_cast<int>(adj.size()); }
};

template <typename T = void>
using digraph = graph<T, true>;
