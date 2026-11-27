#pragma once
#include <bits/stdc++.h>

template <typename T>
class matrix {
private:
  int n = 0, m = 0;
  std::vector<T> data;

public:
  matrix() = default;
  explicit matrix(int n_, int m_, const T& val = {}) : n(n_), m(m_) {
    assert(n >= 0 && m >= 0);
    data.assign(size_t(n) * m, val);
  }
  matrix(std::initializer_list<std::initializer_list<T>> rows) {
    n = int(rows.size());
    m = n ? int(rows.begin()->size()) : 0;
    data.reserve(size_t(n) * m);
    for (const auto& row : rows) {
      assert(int(row.size()) == m);
      data.insert(data.end(), row.begin(), row.end());
    }
  }

  static matrix identity(int n) {
    matrix res(n, n);
    for (int i = 0; i < n; i++) res[i][i] = T(1);
    return res;
  }

  auto operator[](int i) {
    assert(0 <= i && i < n);
    return std::span<T>(data).subspan(size_t(i) * m, m);
  }
  auto operator[](int i) const {
    assert(0 <= i && i < n);
    return std::span<const T>(data).subspan(size_t(i) * m, m);
  }

  matrix& operator+=(const matrix& rhs) {
    assert(n == rhs.n && m == rhs.m);
    for (size_t i = 0; i < data.size(); i++) data[i] += rhs.data[i];
    return *this;
  }
  matrix& operator-=(const matrix& rhs) {
    assert(n == rhs.n && m == rhs.m);
    for (size_t i = 0; i < data.size(); i++) data[i] -= rhs.data[i];
    return *this;
  }
  matrix& operator*=(const matrix& rhs) { return *this = *this * rhs; }

  matrix pow(long long exp) const {
    assert(n == m && exp >= 0);
    matrix res = identity(n), a = *this;
    while (exp > 0) {
      if (exp & 1) res *= a;
      a *= a;
      exp >>= 1;
    }
    return res;
  }

  int rows() const { return n; }
  int cols() const { return m; }
  std::span<T> flat() { return data; }
  std::span<const T> flat() const { return data; }

  friend matrix operator+(matrix lhs, const matrix& rhs) { return lhs += rhs; }
  friend matrix operator-(matrix lhs, const matrix& rhs) { return lhs -= rhs; }
  friend matrix operator*(const matrix& lhs, const matrix& rhs) {
    assert(lhs.m == rhs.n);
    matrix res(lhs.n, rhs.m);
    for (int i = 0; i < lhs.n; i++) {
      for (int k = 0; k < lhs.m; k++) {
        const T& x = lhs.data[size_t(i) * lhs.m + k];
        for (int j = 0; j < rhs.m; j++)
          res.data[size_t(i) * rhs.m + j] += x * rhs.data[size_t(k) * rhs.m + j];
      }
    }
    return res;
  }
  friend bool operator==(const matrix&, const matrix&) = default;
};
