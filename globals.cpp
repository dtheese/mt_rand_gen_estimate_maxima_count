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
                                       TRIALS / 2, // Ensure each thread has at least 2 trials
                                       MAX_THREADS
                                    }
                                 )
                           };

const chrono::time_point<chrono::steady_clock> start_time{chrono::steady_clock::now()};
