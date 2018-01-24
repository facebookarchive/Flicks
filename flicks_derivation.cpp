/**
 * Copyright (c) 2017-present, Facebook, Inc.
 * All rights reserved.
 * 
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#if __cplusplus >= 201703L
#include <numeric>
#endif

namespace derivation_of_flicks {

#if __cplusplus > 201402L
using std::lcm;
#else
template <typename T>
T gcd(T a, T b) {
  for (;;) {
    if (a == 0) return b;
    b %= a;
    if (b == 0) return a;
    a %= b;
  } 
}

template <typename A, typename B>
std::common_type_t<A, B> lcm(A a, B b) {
  return a / gcd<std::common_type_t<A, B>>(a, b) * b;
}
#endif

int64_t find_biggest_denom_under_nano() {
  int64_t x = 1;

  // These are the image-frame-rate measures, all multiplied by 1000 for
  // reasonable room in simulation substeps
  x = lcm(x, 24000);
  x = lcm(x, 25000);
  x = lcm(x, 30000);
  x = lcm(x, 48000);
  x = lcm(x, 50000);
  x = lcm(x, 60000);
  x = lcm(x, 90000);
  x = lcm(x, 100000);
  x = lcm(x, 120000);

  // These are a set of audio sample rates
  x = lcm(x, 8000);
  x = lcm(x, 16000);
  x = lcm(x, 22050);
  x = lcm(x, 24000);
  x = lcm(x, 32000);
  x = lcm(x, 44100);
  x = lcm(x, 48000);
  x = lcm(x, 88200);
  x = lcm(x, 96000);
  x = lcm(x, 192000);

  return x <= 1000000000LL ? x : 0;
}

void print_line(int64_t measure, int64_t denom) {
  std::cout << "//! 1/" << measure << " fps frame:     " << denom / measure
            << " Flicks" << std::endl;
}

void print_flicks_result() {
  const int64_t denom = find_biggest_denom_under_nano();
  std::cout << "Value = " << denom << std::endl;
  print_line(24, denom);
  print_line(25, denom);
  print_line(30, denom);
  print_line(48, denom);
  print_line(50, denom);
  print_line(60, denom);
  print_line(90, denom);
  print_line(100, denom);
  print_line(120, denom);
  print_line(8000, denom);
  print_line(16000, denom);
  print_line(22050, denom);
  print_line(24000, denom);
  print_line(32000, denom);
  print_line(44100, denom);
  print_line(48000, denom);
  print_line(88200, denom);
  print_line(96000, denom);
  print_line(192000, denom);
}

}  // namespace derivation_of_flicks

int main(int argc, char* argv[]) {
  derivation_of_flicks::print_flicks_result();
  return 0;
}
