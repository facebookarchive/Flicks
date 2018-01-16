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

namespace util {

//! A flick (frame-tick) is a very small unit of time. It is 1/705600000 of a
//! second, exactly. This unit of time is the smallest time unit which is LARGER
//! than a nanosecond, and can in integer quantities exactly represent a single
//! frame duration for 24hz, 25hz, 30hz, 48hz, 50hz, 60hz, 90hz, 100hz, 120hz,
//! and also 1/1000 divisions of each. This makes it suitable for use via
//! std::chrono::duration and std::ratio for doing timing work against the
//! system high resolution clock, which is in nanoseconds, but doesn't get
//! slightly out of sync when doing common frame rates.
//!
//! In order to accomodate media playback, we also support some common audio
//! sample rates as well. This list is not exhaustive, but covers the majority
//! of digital audio formats. They are 8kHz, 16kHz, 22.05kHz, 24kHz,
//! 32kHz, 44.1kHz, 48kHz, 88.2kHz, 96kHz, and 192kHz. While humans can't hear
//! higher than 48kHz, the higher sample rates are used for working audio files
//! which might later be resampled or retimed.
//!
//! The NTSC variations (~29.97, etc) are actually defined as 24 * 1000/1001 and
//! 30 * 1000/1001, which are impossible to represent exactly in a way where 1
//! second is exact, so we don't bother - they'll be inexact in any
//! circumstance.
//!
//! 1/24 fps frame:     29400000 flicks
//! 1/25 fps frame:     28224000 flicks
//! 1/30 fps frame:     23520000 flicks
//! 1/48 fps frame:     14700000 flicks
//! 1/50 fps frame:     14112000 flicks
//! 1/60 fps frame:     11760000 flicks
//! 1/90 fps frame:     7840000 flicks
//! 1/100 fps frame:     7056000 flicks
//! 1/120 fps frame:     5880000 flicks
//! 1/8000 fps frame:     88200 flicks
//! 1/16000 fps frame:     44100 flicks
//! 1/22050 fps frame:     32000 flicks
//! 1/24000 fps frame:     29400 flicks
//! 1/32000 fps frame:     22050 flicks
//! 1/44100 fps frame:     16000 flicks
//! 1/48000 fps frame:     14700 flicks
//! 1/88200 fps frame:     8000 flicks
//! 1/96000 fps frame:     7350 flicks
//! 1/192000 fps frame:     3675 flicks

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
inline constexpr double to_seconds(const flicks ns) {
  return std::chrono::duration_cast<std::chrono::duration<double>>(ns).count();
}

//! Convert doubles (as seconds) to flicks
//!
inline constexpr flicks to_flicks(const double s) {
  return std::chrono::duration_cast<flicks>(std::chrono::duration<double>{s});
}

//! Convert a regular duration to flicks
//!
template <class Rep, class Period>
inline constexpr flicks flicks_cast(
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
