// compile with
#include <vector>
#include <iostream>

#include <sycl/execution_policy>
#include <experimental/algorithm>
#include <sycl/helpers/sycl_buffers.hpp>

using namespace std::experimental::parallel;
using namespace sycl::helpers;

int main() {
  constexpr size_t array_size = 1024*512;
  std::array<cl::sycl::cl_int, array_size> a;
  std::iota(begin(a),end(a),0);

  {
    cl::sycl::buffer<int> b(a.data(), cl::sycl::range<1>(a.size()));
    cl::sycl::queue q;
    sycl::sycl_execution_policy<class Mul> sycl_policy(q);
    transform(sycl_policy, begin(b), end(b), begin(b),
              [](int x) { return x*2; });
  }

  auto printer = [](const auto& in) {std::cout << " " << in ;};
  std::for_each(a.cbegin(), a.cend(), printer);

}
