#pragma once
#include <bits/stdc++.h>

template <typename T>
class binomial {
private:
  std::vector<T> fac, ifac;

public:
  explicit binomial(int n) {
    assert(n >= 0);
    fac.resize(n + 1);
    ifac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
      fac[i] = fac[i - 1] * i;
    }
    ifac[n] = T(1) / fac[n];
    for (int i = n; i > 0; i--) {
      ifac[i - 1] = ifac[i] * i;
    }
  }

  T fact(int n) const { assert(0 <= n && n < int(fac.size())); return fac[n]; }
  T ifact(int n) const { assert(0 <= n && n < int(ifac.size())); return ifac[n]; }

  T comb(int n, int k) const {
    assert(0 <= n && n < int(fac.size()));
    return k < 0 || k > n ? T(0) : fac[n] * ifac[k] * ifac[n - k];
  }

  T perm(int n, int k) const {
    assert(0 <= n && n < int(fac.size()));
    return k < 0 || k > n ? T(0) : fac[n] * ifac[n - k];
  }
};
