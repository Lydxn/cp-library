#pragma once
#include <bits/stdc++.h>

// phi(x) = no. of coprime integers below x
std::vector<int> phi_sieve(int n) {
  std::vector<int> ret(n + 1);
  std::iota(ret.begin(), ret.end(), 0);
  for (int i = 2; i <= n; i++) {
    if (ret[i] == i) {
      for (int j = i; j <= n; j += i) {
        ret[j] -= ret[j] / i;
      }
    }
  }
  return ret;
}

// spf(x) = smallest prime factor of x
std::vector<int> spf_sieve(int n) {
  std::vector<int> spf(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!spf[i]) {
      for (int j = i; j <= n; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
  }
  return spf;
}

// gpf(x) = greatest prime factor of x
std::vector<int> gpf_sieve(int n) {
  std::vector<int> gpf(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!gpf[i]) {
      for (int j = i; j <= n; j += i) {
        gpf[j] = i;
      }
    }
  }
  return gpf;
}

// mu(x) = Mobius function of x
std::vector<int> mu_sieve(int n) {
  std::vector<int> mu(n + 1, 1);
  std::vector<bool> prime(n + 1, true);
  mu[0] = 0;
  for (int i = 2; i <= n; i++) {
    if (prime[i]) {
      for (int j = i; j <= n; j += i) {
        prime[j] = false;
        mu[j] = -mu[j];
      }
      int64_t sq = int64_t(i) * i;
      for (int64_t j = sq; j <= n; j += sq) {
        mu[j] = 0;
      }
    }
  }
  return mu;
}
