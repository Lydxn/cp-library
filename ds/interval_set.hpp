#pragma once
#include <bits/stdc++.h>

template <typename T>
class interval_set {
  std::map<T, T> data;

public:
  using const_iterator = typename std::map<T, T>::const_iterator;

  void add(T l, T r) {
    assert(l <= r);
    if (l == r) return;
    auto it = data.lower_bound(l);
    if (it != data.begin() && std::prev(it)->second >= l) --it;
    while (it != data.end() && it->first <= r) {
      l = std::min(l, it->first);
      r = std::max(r, it->second);
      it = data.erase(it);
    }
    data.emplace_hint(it, std::move(l), std::move(r));
  }

  void erase(const T& l, const T& r) {
    assert(l <= r);
    if (l == r) return;
    auto it = data.lower_bound(l);
    if (it != data.begin() && std::prev(it)->second > l) --it;
    while (it != data.end() && it->first < r) {
      auto [a, b] = *it;
      it = data.erase(it);
      if (a < l) data.emplace(a, l);
      if (b > r) data.emplace(r, b);
    }
  }

  const_iterator find(const T& x) const {
    auto it = data.upper_bound(x);
    if (it == data.begin()) return data.end();
    --it;
    return it->second > x ? it : data.end();
  }

  bool contains(const T& x) const { return find(x) != data.end(); }
  bool contains(const T& l, const T& r) const {
    assert(l <= r);
    if (l == r) return true;
    auto it = find(l);
    return it != data.end() && r <= it->second;
  }

  const_iterator find_overlap(const T& l, const T& r) const {
    assert(l <= r);
    if (l == r) return data.end();
    auto it = data.lower_bound(l);
    if (it != data.begin() && std::prev(it)->second > l) --it;
    return it != data.end() && it->first < r ? it : data.end();
  }

  const_iterator lower_bound(const T& x) const { return data.lower_bound(x); }
  const_iterator upper_bound(const T& x) const { return data.upper_bound(x); }
  const_iterator begin() const { return data.begin(); }
  const_iterator end() const { return data.end(); }
  int size() const { return int(data.size()); }
  bool empty() const { return data.empty(); }
  void clear() { data.clear(); }
};
