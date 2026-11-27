#pragma once
#include <bits/stdc++.h>

template <typename M>
class swag_deque {
private:
  using T = std::remove_cvref_t<decltype(M::e())>;
  std::vector<std::pair<T, T>> left, right;

public:
  swag_deque() {
    T e = M::e();
    left.emplace_back(e, e);
    right.emplace_back(e, e);
  }

  void push_back(T x) {
    T agg = M::op(right.back().second, x);
    right.emplace_back(std::move(x), std::move(agg));
  }

  void push_front(T x) {
    T agg = M::op(x, left.back().second);
    left.emplace_back(std::move(x), std::move(agg));
  }

  void pop_back() {
    assert(!empty());
    if (right.size() == 1) {
      size_t k = left.size() / 2;
      right.reserve(k + 1);
      for (size_t i = k; i > 0; i--) push_back(std::move(left[i].first));
      left.erase(left.begin() + 1, left.begin() + k + 1);
      for (size_t i = 1; i < left.size(); i++)
        left[i].second = M::op(left[i].first, left[i - 1].second);
    }
    right.pop_back();
  }

  void pop_front() {
    assert(!empty());
    if (left.size() == 1) {
      size_t k = right.size() / 2;
      left.reserve(k + 1);
      for (size_t i = k; i > 0; i--) push_front(std::move(right[i].first));
      right.erase(right.begin() + 1, right.begin() + k + 1);
      for (size_t i = 1; i < right.size(); i++)
        right[i].second = M::op(right[i - 1].second, right[i].first);
    }
    left.pop_back();
  }

  const T& front() const {
    assert(!empty());
    return left.size() == 1 ? right[1].first : left.back().first;
  }

  const T& back() const {
    assert(!empty());
    return right.size() == 1 ? left[1].first : right.back().first;
  }

  T prod_all() const {
    if (left.size() == 1) return right.back().second;
    if (right.size() == 1) return left.back().second;
    return M::op(left.back().second, right.back().second);
  }

  bool empty() const { return left.size() + right.size() == 2; }
  int size() const { return left.size() + right.size() - 2; }
};
