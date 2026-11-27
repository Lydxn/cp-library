#pragma once
#include <bits/stdc++.h>

template <typename T, typename Compare = std::less<>>
class li_chao_tree {
private:
  struct line {
    T m, b;
    T operator()(T x) const { return m * x + b; }
  };
  struct node {
    line f;
    int ch[2] = {-1, -1};
  };

  T lo, hi;
  std::vector<node> data;
  Compare cmp;

  void add_line(int i, T l, T r, line f) {
    T mid = std::midpoint(l, r);
    if (cmp(f(mid), data[i].f(mid))) std::swap(f, data[i].f);
    if (l == r) return;
    int dir = !cmp(f(l), data[i].f(l));
    int child = data[i].ch[dir];
    if (child == -1) {
      data[i].ch[dir] = int(data.size());
      data.push_back({f});
      return;
    }
    if (dir) add_line(child, mid + 1, r, f);
    else add_line(child, l, mid, f);
  }

  T query(int i, T l, T r, T x) const {
    T cur = data[i].f(x);
    if (l == r) return cur;
    T mid = std::midpoint(l, r);
    int dir = x > mid;
    int child = data[i].ch[dir];
    if (child == -1) return cur;
    T val = dir ? query(child, mid + 1, r, x) : query(child, l, mid, x);
    return cmp(val, cur) ? val : cur;
  }

public:
  li_chao_tree(T lo_, T hi_, Compare cmp_ = {})
    : lo(lo_), hi(hi_), cmp(std::move(cmp_)) {
    assert(lo <= hi);
  }

  void add_line(T m, T b) {
    line f{m, b};
    if (data.empty()) {
      data.push_back({f});
      return;
    }
    add_line(0, lo, hi, f);
  }

  T query(T x) const {
    assert(lo <= x && x <= hi && !data.empty());
    return query(0, lo, hi, x);
  }

  bool empty() const { return data.empty(); }
};
