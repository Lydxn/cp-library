#pragma once
#include <bits/stdc++.h>

namespace detail {
  struct neighbor {
    template <typename E>
    constexpr auto operator()(E&& e) const {
      if constexpr (requires { std::get<0>(e); }) {
        return std::get<0>(e);
      } else {
        return e;
      }
    }
  };

  struct weight {
    template <typename E>
    constexpr auto operator()(E&& e) const {
      if constexpr (requires { std::get<1>(e); }) {
        return std::get<1>(e);
      } else {
        return 1;
      }
    }
  };
}
