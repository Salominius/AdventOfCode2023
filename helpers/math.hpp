#include <numeric>

namespace math {
  template <typename M, typename N>
  constexpr auto lcm(const M& m, const N& n) {
    return std::lcm(m, n);
  }

  template<typename M>
  constexpr auto lcm(const std::vector<M>& v) {
    return std::reduce(v.begin(), v.end(), (M) 1, lcm<M, M>); 
  }
}