/**
 * Copyright (c) 2017-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cstdint>
#include <iostream>

namespace motivation {

// Suppose you were writing a physics simulation of rigid bodies which was going
// to work at 24 frames per second, the frame rate for motion pictures, and you
// wanted to represent time as a large integer to maintain temporal precision
// equally in all parts of your timeline. Or really, you could be doing any task
// that involves iterating through time samples.
//
// In this example, I'll just use integers directly, as the std::chrono notation
// can be somewhat obfuscating.
//
// You want the highest precision, so you choose nanoseconds as your time unit.
// Below illustrates a problem you'll encounter.
//
// The examples below are a simplification of a real problem we ran into in
// production when using nanoseconds, and though it's pretty easy to see in this
// contrived example, we were befuddled for a little while before figuring out
// what the problem actually was. It's certainly possible for us to have worked
// around the problem, continuing to work in nanoseconds while bracketing our
// comparisons and correcting for accumulated errors, but the introduction of
// flicks makes things work correctly without having to think about it (for most
// scenarios).

constexpr int64_t NANOSECONDS_PER_SECOND = 1000000000;

constexpr int64_t FRAMES_PER_SECOND = 24;

constexpr int64_t NANOSECONDS_PER_FRAME =
    NANOSECONDS_PER_SECOND / FRAMES_PER_SECOND;

void failure_example() {
  // Pretend that you're iterating in frames up to six seconds, and you want to
  // print out a counter every time you hit a full second
  const int64_t end_time_ns = 6 * NANOSECONDS_PER_SECOND;
  int iteration_count = 0;
  for (int64_t time_ns = 0; time_ns < end_time_ns;
       time_ns += NANOSECONDS_PER_FRAME) {
    // ... do some work
    if ((time_ns % NANOSECONDS_PER_SECOND) == 0) {
      std::cout << "Second!" << std::endl;
    }

    ++iteration_count;
  }
  if (iteration_count != (6 * FRAMES_PER_SECOND)) {
    std::cerr << "Incorrect number of iterations!" << std::endl;
  } else {
    std::cout << "Correct number of iterations!" << std::endl;
  }

  // The above example will fail in two ways. It will visit too many frames (by
  // 1), and it will only print one time, instead of six.

  // This will illustrate the problem more directly:
  if ((FRAMES_PER_SECOND * NANOSECONDS_PER_FRAME) != NANOSECONDS_PER_SECOND) {
    std::cerr << "Precision error!" << std::endl;
  } else {
    std::cout << "Correct precision!" << std::endl;
  }
}

// Since the nanoseconds example fails, let's try it again with flicks.

constexpr int64_t FLICKS_PER_SECOND = 705600000;

constexpr int64_t FLICKS_PER_FRAME = FLICKS_PER_SECOND / FRAMES_PER_SECOND;

void success_example() {
  // Pretend that you're iterating in frames up to six seconds, and you want to
  // print out a counter every time you hit a full second
  const int64_t end_time_flicks = 6 * FLICKS_PER_SECOND;
  int iteration_count = 0;
  for (int64_t time_flicks = 0; time_flicks < end_time_flicks;
       time_flicks += FLICKS_PER_FRAME) {
    // ... do some work
    if ((time_flicks % FLICKS_PER_SECOND) == 0) {
      std::cout << "Second!" << std::endl;
    }

    ++iteration_count;
  }
  if (iteration_count != (6 * FRAMES_PER_SECOND)) {
    std::cerr << "Incorrect number of iterations!" << std::endl;
  } else {
    std::cout << "Correct number of iterations!" << std::endl;
  }

  // The above example will succeed where the previous example failed. It will
  // print the right number of "Second!" and it will have the right number of
  // iterations.

  // This will illustrate the success more directly:
  if ((FRAMES_PER_SECOND * FLICKS_PER_FRAME) != FLICKS_PER_SECOND) {
    std::cerr << "Precision error!" << std::endl;
  } else {
    std::cout << "Correct precision!" << std::endl;
  }
}

}  // namespace motivation

int main(int argc, char* argv[]) {
  std::cout << "First failure: " << std::endl;
  motivation::failure_example();

  std::cout << "\nThen success: " << std::endl;
  motivation::success_example();
  return 0;
}