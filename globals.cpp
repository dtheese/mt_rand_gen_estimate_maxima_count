#include <algorithm>
#include <thread>

using namespace std;

#include "globals.h"

namespace
{
   const my_uint_t MAX_HW_THREADS{thread::hardware_concurrency()};
}

const my_uint_t NUM_THREADS{
                              min(
                                    {
                                       MAX_HW_THREADS > 0 ? MAX_HW_THREADS : 1,

                                       // Ensure each thread has at least two trials
                                       // since we divide by (TRIALS - 1) at one point
                                       TRIALS / 2,

                                       MAX_THREADS
                                    }
                                 )
                           };

const chrono::time_point<chrono::steady_clock> start_time{chrono::steady_clock::now()};
