#pragma once
#include <bits/stdc++.h>

template <int mod>
class modint {
  static_assert(mod > 0, "modulus must be positive");

private:
  uint32_t val = 0;

public:
  modint() = default;
  template <std::integral T>
  modint(T v) {
    if constexpr (std::signed_integral<T>) {
      long long x = v % mod;
      if (x < 0) x += mod;
      val = static_cast<uint32_t>(x);
    } else {
      val = static_cast<uint32_t>(v % mod);
    }
  }

  // internal accessor
  uint32_t operator()() const { return val; }

  modint& operator+=(const modint& rhs) {
    if ((val += rhs.val) >= mod) val -= mod;
    return *this;
  }
  modint& operator-=(const modint& rhs) {
    val = val >= rhs.val ? val - rhs.val : val + mod - rhs.val;
    return *this;
  }
  modint& operator*=(const modint& rhs) {
    val = uint64_t(val) * rhs.val % mod;
    return *this;
  }
  modint& operator/=(const modint& rhs) {
    return *this *= rhs.inv();
  }
  modint& operator++() { if (++val == mod) val = 0; return *this; }
  modint& operator--() { val = val == 0 ? mod - 1 : val - 1; return *this; }
  modint operator++(int) { auto ret = *this; ++*this; return ret; }
  modint operator--(int) { auto ret = *this; --*this; return ret; }
  modint operator+() const { return *this; }
  modint operator-() const { return modint() - *this; }

  modint pow(long long n) const {
    assert(n >= 0);
    modint ret = 1, a = val;
    while (n > 0) {
      if (n & 1) ret *= a;
      a *= a;
      n >>= 1;
    }
    return ret;
  }

  modint inv() const {
    int a = val, b = mod, u = 1, v = 0;
    while (b > 0) {
      int t = a / b;
      a -= t * b; std::swap(a, b);
      u -= t * v; std::swap(u, v);
    }
    assert(a == 1);
    return modint(u);
  }

  friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }
  friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }
  friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }
  friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }
  friend auto operator<=>(const modint& lhs, const modint& rhs) = default;

  friend std::istream& operator>>(std::istream& is, modint& m) {
    long long v; is >> v; m = v;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const modint& m) { return os << m.val; }
};

constexpr int mod = 1e9 + 7;
using mint = modint<mod>;
