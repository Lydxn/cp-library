#pragma once
#include <bits/stdc++.h>

class modint61 {
public:
  static constexpr uint64_t mod = (uint64_t(1) << 61) - 1;

private:
  uint64_t val = 0;

public:
  modint61() = default;
  template <std::integral T>
  modint61(T v) {
    if constexpr (std::signed_integral<T>) {
      __int128_t x = static_cast<__int128_t>(v) % mod;
      if (x < 0) x += mod;
      val = static_cast<uint64_t>(x);
    } else {
      val = static_cast<uint64_t>(static_cast<__uint128_t>(v) % mod);
    }
  }

  // internal accessor
  uint64_t operator()() const { return val; }

  modint61& operator+=(const modint61& rhs) {
    if ((val += rhs.val) >= mod) val -= mod;
    return *this;
  }
  modint61& operator-=(const modint61& rhs) {
    val = val >= rhs.val ? val - rhs.val : val + mod - rhs.val;
    return *this;
  }
  modint61& operator*=(const modint61& rhs) {
    __uint128_t p = __uint128_t(val) * rhs.val;
    val = static_cast<uint64_t>(p >> 61) + static_cast<uint64_t>(p & mod);
    if (val >= mod) val -= mod;
    return *this;
  }
  modint61& operator/=(const modint61& rhs) {
    return *this *= rhs.inv();
  }
  modint61& operator++() { if (++val == mod) val = 0; return *this; }
  modint61& operator--() { val = val == 0 ? mod - 1 : val - 1; return *this; }
  modint61 operator++(int) { auto ret = *this; ++*this; return ret; }
  modint61 operator--(int) { auto ret = *this; --*this; return ret; }
  modint61 operator+() const { return *this; }
  modint61 operator-() const { return modint61() - *this; }

  modint61 pow(long long n) const {
    assert(n >= 0);
    modint61 ret = 1, a = val;
    while (n > 0) {
      if (n & 1) ret *= a;
      a *= a;
      n >>= 1;
    }
    return ret;
  }

  modint61 inv() const {
    assert(val != 0);
    return pow(mod - 2);
  }

  friend modint61 operator+(modint61 lhs, const modint61& rhs) { return lhs += rhs; }
  friend modint61 operator-(modint61 lhs, const modint61& rhs) { return lhs -= rhs; }
  friend modint61 operator*(modint61 lhs, const modint61& rhs) { return lhs *= rhs; }
  friend modint61 operator/(modint61 lhs, const modint61& rhs) { return lhs /= rhs; }
  friend auto operator<=>(const modint61& lhs, const modint61& rhs) = default;

  friend std::istream& operator>>(std::istream& is, modint61& m) {
    long long v; is >> v; m = v;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const modint61& m) { return os << m.val; }
};
