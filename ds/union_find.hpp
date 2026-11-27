#pragma once
#include <bits/stdc++.h>

class union_find {
private:
  int cnt = 0;
  std::vector<int> data;

public:
  union_find() = default;
  explicit union_find(int n) : cnt(n), data(n, -1) {}

  int find(int u) {
    assert(0 <= u && u < int(data.size()));
    if (data[u] < 0) return u;
    return data[u] = find(data[u]);
  }

  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (data[u] > data[v]) std::swap(u, v);
    data[u] += data[v];
    data[v] = u;
    --cnt;
    return true;
  }

  bool same(int u, int v) { return find(u) == find(v); }
  int size(int u) { return -data[find(u)]; }
  int count() { return cnt; }
};
