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

namespace derivation_of_flicks {

template <int64_t measure>
constexpr bool test_measure(const int64_t v) {
  return (v % measure) == 0;
}

constexpr bool test(const int64_t v) {
  return
      // These are the image-frame-rate measures, all multiplied by 1000 for
      // reasonable room in simulation substeps
      test_measure<24000>(v) && test_measure<25000>(v) &&
      test_measure<30000>(v) && test_measure<48000>(v) &&
      test_measure<50000>(v) && test_measure<60000>(v) &&
      test_measure<90000>(v) && test_measure<100000>(v) &&
      test_measure<120000>(v) &&

      // These are a set of audio sample rates
      test_measure<8000>(v) && test_measure<16000>(v) &&
      test_measure<22050>(v) && test_measure<24000>(v) &&
      test_measure<32000>(v) && test_measure<44100>(v) &&
      test_measure<48000>(v) && test_measure<88200>(v) &&
      test_measure<96000>(v) && test_measure<192000>(v);
}

int64_t find_biggest_denom_under_nano() {
  for (int64_t i = 1000000000LL; i > 0; --i) {
    if (test(i)) {
      return i;
    }
  }

  return 0;
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
