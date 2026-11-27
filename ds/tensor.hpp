#pragma once
#include <bits/stdc++.h>

template <typename T, size_t dim>
class tensor {
  static_assert(dim > 0, "number of dimensions must be positive");

private:
  std::vector<T> data;
  std::array<size_t, dim> dims;
  std::array<size_t, dim> strides;

  template <size_t D, typename U>
  struct view {
    U* data;
    const std::array<size_t, dim>& dims;
    const std::array<size_t, dim>& strides;

    decltype(auto) operator[](size_t i) const {
      assert(i < dims[dim - D]);
      if constexpr (D == 1) {
        return data[i];
      } else {
        return view<D - 1, U>{
          data + i * strides[dim - D],
          dims,
          strides,
        };
      }
    }
  };

  void init(std::array<size_t, dim> dims_, const T& fill = {}) {
    dims = dims_;
    size_t total = 1;
    for (size_t i = dim; i-- > 0; ) {
      strides[i] = total;
      total *= dims[i];
    }
    data.assign(total, fill);
  }

public:
  template <typename... Args>
  requires(sizeof...(Args) == dim || sizeof...(Args) == dim + 1)
  explicit tensor(Args&&... args) : dims{}, strides{} {
    if constexpr (sizeof...(Args) == dim) {
      init({static_cast<size_t>(args)...}, T{});
    } else {
      auto tuple = std::forward_as_tuple(std::forward<Args>(args)...);
      [&]<size_t... Is>(std::index_sequence<Is...>) {
        init(
          {static_cast<size_t>(std::get<Is>(tuple))...},
          T(std::get<dim>(tuple))
        );
      }(std::make_index_sequence<dim>{});
    }
  }

  decltype(auto) operator[](size_t i) { return view<dim, T>{data.data(), dims, strides}[i]; }
  decltype(auto) operator[](size_t i) const { return view<dim, const T>{data.data(), dims, strides}[i]; }

  size_t size() const { return data.size(); }
  const auto& shape() const { return dims; }
  std::span<T> flat() { return data; }
  std::span<const T> flat() const { return data; }
};
