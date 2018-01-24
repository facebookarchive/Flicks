# Flicks

## Basics
A flick (frame-tick) is a very small unit of time. It is 1/705600000 of a second, exactly.

    1 flick = 1/705600000 second

This unit of time is the smallest time unit which is LARGER than a nanosecond,
and can in integer quantities exactly represent a single frame duration for
24hz, 25hz, 30hz, 48hz, 50hz, 60hz, 90hz, 100hz, 120hz, and also 1/1000 divisions of each.
This makes it suitable for use via std::chrono::duration and std::ratio for doing timing work
against the system high resolution clock, which is in nanoseconds, but doesn't get slightly
out of sync when doing common frame rates.

In order to accomodate media playback, we also support some common audio sample rates
as well. This list is not exhaustive, but covers the majority of digital audio formats.
They are 8kHz, 16kHz, 22.05kHz, 24kHz, 32kHz, 44.1kHz, 48kHz, 88.2kHz, 96kHz, and 192kHz.
While humans can't hear higher than 48kHz, the higher sample rates are used for working
audio files which might later be resampled or retimed.

The NTSC variations (~23.976, ~29.97, etc) are actually defined as 24 * 1000/1001 and
30 * 1000/1001, etc. They can be represented exactly in flicks, but 1/1000 divisions are not
available.

## Details

* 1/24 fps frame:     29400000 flicks
* 1/25 fps frame:     28224000 flicks
* 1/30 fps frame:     23520000 flicks
* 1/48 fps frame:     14700000 flicks
* 1/50 fps frame:     14112000 flicks
* 1/60 fps frame:     11760000 flicks
* 1/90 fps frame:     7840000 flicks
* 1/100 fps frame:     7056000 flicks
* 1/120 fps frame:     5880000 flicks
* 1/8000 fps frame:     88200 flicks
* 1/16000 fps frame:     44100 flicks
* 1/22050 fps frame:     32000 flicks
* 1/24000 fps frame:     29400 flicks
* 1/32000 fps frame:     22050 flicks
* 1/44100 fps frame:     16000 flicks
* 1/48000 fps frame:     14700 flicks
* 1/88200 fps frame:     8000 flicks
* 1/96000 fps frame:     7350 flicks
* 1/192000 fps frame:     3675 flicks

NTSC rates:

* 1001/24000 (~23.976) fps frame:    29429400 flicks
* 1001/30000 (~29.97) fps frame:     23543520 flicks
* 1001/60000 (~59.94) fps frame:     11771760 flicks
* 1001/120000 (~119.88) fps frame:    5885880 flicks

## Motivation

When working creating visual effects for film, television, and other media, it is common
to run simulations or other time-integrating processes which subdivide a single frame of time
into a fixed, integer number of subdivisions. It is handy to be able to accumulate these 
subdivisions to create exact 1-frame and 1-second intervals, for a variety of reasons. 

Knowing that you should never, ever use floating point representations for accumulated, 
simulated time (lest your temporal accuracy degrade over time), the std::chrono time tools
in C++ are ideal. However, the highest usable resolution, nanoseconds, doesn't evenly divide
common film & media framerates. This was the genesis of this unit.

## Acknowledgements

This time unit began as a technical question posted publicly on Facebook by Christopher Horvath
in early 2017. Many people contributed and refined the unit, including Dan Goldman, Pascal Pincosy,
Simon Eves, Kearsley Higgins, Francisco De La Torre, Benjy Feen, Eric Landreneau and Sebastian Sylwan,
among others. Here's the post!
https://www.facebook.com/christopher.horvath.395/posts/1157292757692660

## Installation
Just place flicks.h wherever you install C++ header files - this is a header only library. Flicks are placed
in the "util" namespace here, for lack of a clear alternative. It would be nice if they were in std:: someday.

## Derivation
A C++ file which implements a derivation of flicks is provided - it is not required to use the library,
but only to show how it was derived. A brute-force approach was intentionally used. To compile, assuming
you have a C++ compiler installed, just do this:

    > c++ -o flicks_derivation flicks_derivation.cpp -std=c++14; ./flicks_derivation

## Test
A C++ file which tests flicks is provided - it is not required to use the library,
but only to test the unit. To compile, assuming you have a C++ compiler installed, just do this:

    > c++ -o flicks_test flicks_test.cpp -std=c++14; ./flicks_test

## Makefile
A makefile is provided that works on a Linuxy system or OSX, but not Windows. To use it:

    > make

To clean up:

    > make clean

## License

    BSD License

    For Flicks software

    Copyright (c) 2017-present, Facebook, Inc. All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
    
     * Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    
     * Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

     * Neither the name Facebook nor the names of its contributors may be used to
       endorse or promote products derived from this software without specific
       prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


