#pragma once
#include <bits/stdc++.h>

template <typename M>
class sparse_table {
private:
  using T = std::remove_cvref_t<decltype(M::e())>;
  int n = 0;
  std::vector<std::vector<T>> data;

  void build(std::vector<T> init) {
    n = int(init.size());
    if (n == 0) return;
    int b = std::bit_width(unsigned(n));
    data.assign(b, std::vector<T>(n));
    data[0] = std::move(init);
    for (int i = 1; i < b; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        data[i][j] = M::op(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

public:
  sparse_table() = default;
  template <std::ranges::input_range R>
  explicit sparse_table(R&& r) {
    std::vector<T> init;
    std::ranges::copy(r, std::back_inserter(init));
    build(std::move(init));
  }
  template <typename G>
  requires std::invocable<G&, int>
  explicit sparse_table(int n_, G gen) {
    assert(n_ >= 0);
    std::vector<T> init;
    init.reserve(n_);
    for (int i = 0; i < n_; i++) init.push_back(std::invoke(gen, i));
    build(std::move(init));
  }

  T prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return M::e();
    int b = std::bit_width(unsigned(r - l)) - 1;
    return M::op(data[b][l], data[b][r - (1 << b)]);
  }

  int size() const { return n; }
};
