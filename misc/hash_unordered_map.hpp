#pragma once
#include <bits/stdc++.h>

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
  };

  template <typename T>
  size_t operator()(const T& x) const {
    static const uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
    return static_cast<size_t>(splitmix64(x + seed));
  }
};
