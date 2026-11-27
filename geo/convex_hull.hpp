#pragma once
#include <bits/stdc++.h>
#include "geo/point.hpp"

template <typename T>
std::vector<point<T>> convex_hull(std::vector<point<T>> p, bool keep_collinear = false) {
  std::sort(p.begin(), p.end());
  p.erase(std::unique(p.begin(), p.end()), p.end());
  int n = p.size();
  if (n <= 2) return p;
  if (keep_collinear) {
    bool line = true;
    for (int i = 2; i < n; i++)
      line &= p[0].cross(p[1], p[i]) == 0;
    if (line) return p;
  }
  auto bad = [&](const auto &a, const auto &b, const auto &c) {
    auto cr = a.cross(b, c);
    return keep_collinear ? cr < 0 : cr <= 0;
  };
  std::vector<point<T>> hull(2 * n);
  int k = 0;
  for (const auto &q : p) {
    while (k >= 2 && bad(hull[k - 2], hull[k - 1], q)) k--;
    hull[k++] = q;
  }
  for (int i = n - 2, lower = k + 1; i >= 0; i--) {
    while (k >= lower && bad(hull[k - 2], hull[k - 1], p[i])) k--;
    hull[k++] = p[i];
  }
  hull.resize(k - 1);
  return hull;
}
