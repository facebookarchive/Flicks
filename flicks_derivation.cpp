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
#include <iomanip>
#include <iostream>

namespace derivation_of_flicks {

template <int64_t measure>
bool test_measure(const int64_t v) {
  // This directly tests that the division is even
  return (v % measure) == 0;
}

template <int64_t ntsc_approx_measure>
bool test_ntsc_approx_measure(const int64_t v) {
  // NTSC hits 1000 frames every (ntsc_approx_measure * 1001) seconds,
  // so we test for that exactly.
  const int64_t units_per_frame = 1001 * (v / (ntsc_approx_measure * 1000));
  return ((v * 1001) % units_per_frame) == 0;
}

bool test(const int64_t v) {
  return
      // These are the image-frame-rate measures, all multiplied by 1000 for
      // reasonable room in simulation substeps
      test_measure<24000>(v) && test_measure<25000>(v) &&
      test_measure<30000>(v) && test_measure<48000>(v) &&
      test_measure<50000>(v) && test_measure<60000>(v) &&
      test_measure<90000>(v) && test_measure<100000>(v) &&
      test_measure<120000>(v) &&

      // These are NTSC
      test_ntsc_approx_measure<24>(v) && test_ntsc_approx_measure<30>(v) &&
      test_ntsc_approx_measure<60>(v) && test_ntsc_approx_measure<120>(v) &&

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

void print_line(const int64_t measure, const int64_t denom) {
  std::cout << "//! " << measure << " fps frame:     " << denom / measure
            << " Flicks" << std::endl;
}

void print_ntsc_approx_line(const int64_t measure, const int64_t denom) {
  // 24 * 1000/1001 (~23.976) fps frame:
  std::cout << "//! " << measure << " * 1000/1001 (~" << std::setprecision(3)
            << std::fixed << static_cast<double>(measure) * 1000.0 / 1001.0
            << ") fps frame:     " << 1001 * (denom / (measure * 1000))
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

  std::cout << std::endl;

  print_ntsc_approx_line(24, denom);
  print_ntsc_approx_line(30, denom);
  print_ntsc_approx_line(60, denom);
  print_ntsc_approx_line(120, denom);
}

}  // namespace derivation_of_flicks

int main(int argc, char* argv[]) {
  derivation_of_flicks::print_flicks_result();
  return 0;
}
