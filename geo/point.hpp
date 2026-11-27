#pragma once
#include <bits/stdc++.h>

template <typename T>
struct point {
  using W = std::conditional_t<std::is_integral_v<T>, __int128_t, T>;

  T x{}, y{};

  point() = default;
  point(T x_, T y_) : x(x_), y(y_) {}

  auto operator<=>(const point&) const = default;

  point& operator+=(const point& p) {
    x += p.x, y += p.y;
    return *this;
  }
  point& operator-=(const point& p) {
    x -= p.x, y -= p.y;
    return *this;
  }
  point& operator*=(const T& k) {
    x *= k, y *= k;
    return *this;
  }
  point& operator/=(const T& k) {
    x /= k, y /= k;
    return *this;
  }

  point operator+() const { return *this; }
  point operator-() const { return {-x, -y}; }

  friend point operator+(point p, const point& q) { return p += q; }
  friend point operator-(point p, const point& q) { return p -= q; }
  friend point operator*(point p, const T& k) { return p *= k; }
  friend point operator*(const T& k, point p) { return p *= k; }
  friend point operator/(point p, const T& k) { return p /= k; }

  W dot(const point& p) const { return W(x) * p.x + W(y) * p.y; }
  W cross(const point& p) const { return W(x) * p.y - W(y) * p.x; }
  W cross(const point& a, const point& b) const {
    return (W(a.x) - x) * (W(b.y) - y) - (W(a.y) - y) * (W(b.x) - x);
  }
  W norm2() const { return dot(*this); }
  W dist2(const point& p) const {
    W dx = W(x) - p.x, dy = W(y) - p.y;
    return dx * dx + dy * dy;
  }
  point perp() const { return {-y, x}; }

  friend std::istream& operator>>(std::istream& is, point& p) {
    return is >> p.x >> p.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const point& p) {
    return os << p.x << ' ' << p.y;
  }
};
