#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

#include <chrono>
#include <limits>

using namespace std;

#include "fundamental_types.h"

// constexpr my_uint_t N{numeric_limits<my_uint_t>::max()};
constexpr my_uint_t N{1'000'000};

constexpr my_uint_t M{20};
constexpr my_uint_t TRIALS{10'000'000'000};

// By default, the lesser of the maximum number of threads the hardware
// will support OR the maximum number of threads that can be used and
// still ensure each thread conducts at least two trials will be used.
// This constant allows limiting the number of threads to a lower value.
constexpr my_uint_t MAX_THREADS{numeric_limits<my_uint_t>::max()};

// Ensure that N, and M are positive.
static_assert(N >= 1);
static_assert(M >= 1);

// Ensure that TRIALS is > 1 since we divide by (TRIALS - 1) at one point.
static_assert(TRIALS > 1);

extern const my_uint_t NUM_THREADS;
extern const chrono::time_point<chrono::steady_clock> start_time;

#endif
