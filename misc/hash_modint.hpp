#pragma once
#include "math/modint.hpp"

namespace std {
  template <int mod>
  struct hash<modint<mod>> {
    size_t operator()(const modint<mod>& m) const {
      return hash<uint32_t>{}(m());
    }
  };
}
