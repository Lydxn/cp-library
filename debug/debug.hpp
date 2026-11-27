#pragma once
#include <bits/stdc++.h>

namespace debug {
  template <class T>
  concept string_like = std::convertible_to<T, std::string_view>;

  template <class T>
  concept tuple_like = requires { typename std::tuple_size<std::remove_cvref_t<T>>::type; };

  template <class T>
  concept queue_like = requires(T x) { x.empty(); x.front(); x.pop(); };

  template <class T>
  concept stack_like = requires(T x) { x.empty(); x.top(); x.pop(); };

  template <class T>
  void print(std::ostream& os, const T& x) {
    if constexpr (string_like<T>) {
      os << '"' << x << '"';
    } else if constexpr (tuple_like<T>) {
      os << '(';
      size_t i = 0;
      std::apply([&](const auto&... y) {
        ((os << (i++ ? ", " : ""), print(os, y)), ...);
      }, x);
      os << ')';
    } else if constexpr (queue_like<T> || stack_like<T>) {
      auto tmp = x;
      os << '{';
      bool first = true;
      while (!tmp.empty()) {
        if (!first) os << ", ";
        first = false;
        if constexpr (queue_like<T>) {
          print(os, tmp.front());
        } else {
          print(os, tmp.top());
        }
        tmp.pop();
      }
      os << '}';
    } else if constexpr (std::ranges::input_range<T>) {
      os << '[';
      bool first = true;
      for (const auto& y : x) {
        if (!first) os << ", ";
        first = false;
        print(os, y);
      }
      os << ']';
    } else {
      os << x;
    }
  }

  template <class... Ts>
  void out(const char* names, const Ts&... xs) {
    std::cerr << '(' << names << ") = (";
    size_t i = 0;
    ((std::cerr << (i++ ? ", " : ""), print(std::cerr, xs)), ...);
    std::cerr << ")\n";
  }
}

#ifdef LOCAL
#define dbg(...) debug::out(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#endif
