namespace detail {
  template <typename T, typename I>
  struct graph_edge { I from, to; T val; };
  template <typename I>
  struct graph_edge<void, I> { I from, to; };
}
