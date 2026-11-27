#pragma once
#include <bits/stdc++.h>

template <typename T>
T phi(T n) {
  assert(n > 0);
  T ret = n;
  for (T i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ret -= ret / i;
      do {
        n /= i;
      } while (n % i == 0);
    }
  }
  return n > 1 ? ret - ret / n : ret;
}
