#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using std_clock = std::chrono::high_resolution_clock;

std::uintptr_t fixed6(std::uintptr_t a, std::uintptr_t b, std::uintptr_t c,
                      std::uintptr_t d, std::uintptr_t e, std::uintptr_t f) {
  return a + b + c + d + e + f;
}

std::uintptr_t vari() { return 0; }

template <typename... inttypes> //
std::uintptr_t vari(std::uintptr_t v0, inttypes... rest) {
  return v0 + vari(rest...);
}

template <typename proc_t>
void bench(char const *title, std::uintptr_t num, proc_t proc) {
  auto t0 = std_clock::now();
  std::uintptr_t sum = 0;
  for (std::uintptr_t i = 0; i < num; ++i) {
    sum += proc(i & 1, i & 2, i & 4, i & 8, i & 16, i & 32);
  }
  auto t1 = std_clock::now();
  auto diff_us =
      std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
  std::cout << title << " " << (diff_us * 1e-6) << "ms " << sum << std::endl;
}

int main(int argc, char const *argv[]) {
  std::uintptr_t num = argc < 2 ? 100 : std::atoi(argv[1]);
  using u = std::uintptr_t;
  for (std::uintptr_t i = 0; i < 3; ++i) {
    bench("fixed", num, fixed6);
    bench("fixed(L)", num, [](u a, u b, u c, u d, u e, u f) -> u {
      return fixed6(a, b, c, d, e, f);
    });
    bench("vari(F)", num, vari<u, u, u, u, u>);
    bench("vari(L)", num, [](u a, u b, u c, u d, u e, u f) -> u {
      return vari(a, b, c, d, e, f);
    });
  }
}