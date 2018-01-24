/**
 * Copyright (c) 2017-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <ratio>

namespace util {

//! A flick (frame-tick) is a very small unit of time. It is 1/705600000 of a second, exactly.
//! 
//!   1 flick = 1/705600000 second
//!
//! This unit of time is the smallest time unit which is LARGER than a nanosecond,
//! and can in integer quantities exactly represent a single frame duration for
//! 24 Hz, 25 Hz, 30 Hz, 48 Hz, 50 Hz, 60 Hz, 90 Hz, 100 Hz, 120 Hz, and also 1/1000 divisions of each, 
//! as well as a single sample duration for 8 kHz, 16 kHz, 22.05 kHz, 24 kHz, 32 kHz, 44.1 kHz, 
//! 48 kHz, 88.2 kHz, 96 kHz, and 192kHz, as well as the NTSC frame durations for
//! 24 * (1000/1001) Hz, 30 * (1000/1001) Hz, 60 * (1000/1001) Hz, and 120 * (1000/1001) Hz.
//!
//! That above was one hell of a run-on sentence, but it's strictly and completely correct in its 
//! description of the unit.
//!
//! This makes flicks suitable for use via std::chrono::duration and std::ratio for doing timing work
//! against the system high resolution clock, which is in nanoseconds, but doesn't get slightly
//! out of sync when doing common frame rates.
//! 
//! We also support some common audio sample rates as well. This list is not exhaustive, but covers 
//! the majority of digital audio formats. They are 8kHz, 16kHz, 22.05kHz, 24kHz, 32kHz, 44.1kHz, 
//! 48kHz, 88.2kHz, 96kHz, and 192kHz.
//!
//! Though it is not part of the design criteria, 144 Hz, which some newer monitors refresh at,
//! does work correctly with flicks.
//! 
//! NTSC IS NOT EXPLICITLY SUPPORTED IN ALL OF ITS SUBTLE NUANCES, BUT:
//! The NTSC variations (~23.976, ~29.97, etc) are approximately defined as 24 * 1000/1001 and
//! 30 * 1000/1001, etc. These can be represented exactly in flicks, but 1/1000 divisions are not
//! available. 
//!
//! Many folks online have pointed out that NTSC technically has a variable frame rate,
//! and that this is handled correctly in other media playback libraries such as QuickTime. 
//! The goal of flicks is to provide a simple, convenient std::chrono::duration to work
//! with when writing code that works with simulation and time in media, but not explicitly to 
//! handle complex, variable-rate playback scenarios. So we'll stick with the 1000/1001 approximations, 
//! and leave it at that!
//!
//! Details
//!
//! 24 fps frame:     29400000 flicks
//! 25 fps frame:     28224000 flicks
//! 30 fps frame:     23520000 flicks
//! 48 fps frame:     14700000 flicks
//! 50 fps frame:     14112000 flicks
//! 60 fps frame:     11760000 flicks
//! 90 fps frame:      7840000 flicks
//! 100 fps frame:     7056000 flicks
//! 120 fps frame:     5880000 flicks
//! 8000 fps frame:      88200 flicks
//! 16000 fps frame:     44100 flicks
//! 22050 fps frame:     32000 flicks
//! 24000 fps frame:     29400 flicks
//! 32000 fps frame:     22050 flicks
//! 44100 fps frame:     16000 flicks
//! 48000 fps frame:     14700 flicks
//! 88200 fps frame:      8000 flicks
//! 96000 fps frame:      7350 flicks
//! 192000 fps frame:     3675 flicks
//!
//! NTSC:
//!
//! 24 * 1000/1001 (~23.976) fps frame:    29429400 flicks
//! 30 * 1000/1001 (~29.97)  fps frame:    23543520 flicks
//! 60 * 1000/1001 (~59.94) fps frame:     11771760 flicks
//! 120 * 1000/1001 (~119.88) fps frame:    5885880 flicks

using flicks = std::chrono::duration<std::chrono::nanoseconds::rep,
                                     std::ratio<1, 705600000>>;

//! Useful constants
constexpr flicks k_flicks_zero_seconds{
    std::chrono::duration_cast<flicks>(std::chrono::seconds{0})};
constexpr flicks k_flicks_one_second{
    std::chrono::duration_cast<flicks>(std::chrono::seconds{1})};
constexpr flicks k_flicks_one_twenty_fourth_of_second{
    std::chrono::duration_cast<flicks>(
        std::chrono::duration<flicks::rep, std::ratio<1, 24>>{1})};
constexpr flicks k_flicks_one_ninetieth_of_second{
    std::chrono::duration_cast<flicks>(
        std::chrono::duration<flicks::rep, std::ratio<1, 90>>{1})};
constexpr flicks k_flicks_min_time{std::numeric_limits<flicks::rep>::min()};

//! Convert flicks to seconds as doubles
//!
constexpr double to_seconds(const flicks ns) {
  return std::chrono::duration_cast<std::chrono::duration<double>>(ns).count();
}

//! Convert doubles (as seconds) to flicks
//!
constexpr flicks to_flicks(const double s) {
  return std::chrono::duration_cast<flicks>(std::chrono::duration<double>{s});
}

//! Convert a regular duration to flicks
//!
template <class Rep, class Period>
constexpr flicks flicks_cast(
    const std::chrono::duration<Rep, Period> in_duration) {
  return std::chrono::duration_cast<flicks>(in_duration);
}

//! This is a std::hash-esque hash functor
//!
struct flicks_hash {
  using argument_type = flicks;
  using result_type = size_t;
  result_type operator()(argument_type const& s) const {
    return std::hash<flicks::rep>{}(s.count());
  }
};

}  // namespace util
