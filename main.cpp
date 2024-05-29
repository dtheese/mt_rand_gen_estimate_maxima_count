#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#include "globals.h"
#include "thread_main.h"
#include "utilities.h"

int main()
{
   vector<future<stats_t>> futures;
   vector<stats_t> thread_results{NUM_THREADS};

   // TODO
   // Ensure each thread will conduct the same number of trials. This eases
   // combining of per-thread statistics into overall statistics.
   assert(TRIALS % NUM_THREADS == 0);

   // Ensure each thread conducts more than one trial. This is necessary since
   // one of the calculations each thread performs is a division by
   // (thread_trials - 1).
   assert(TRIALS / NUM_THREADS > 1);

   cout << endl;
   cout << "N                : " << N << endl;
   cout << "M                : " << M << endl;
   cout << "Trials           : " << TRIALS << endl;
   cout << "NUM_THREADS      : " << NUM_THREADS << endl;
   cout << "Trials per thread: " << TRIALS / NUM_THREADS << endl;
   // TODO: Print any extra trials for last thread
   cout << endl;

   for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      futures.push_back(async(launch::async, thread_main, TRIALS / NUM_THREADS));

   for (my_uint_t i{0}; i < NUM_THREADS; ++i)
      thread_results[i] = futures[i].get();

   chrono::time_point<chrono::steady_clock> stop_time{chrono::steady_clock::now()};
   auto ticks_taken{stop_time - start_time};
   constexpr long double tick_interval{decltype(ticks_taken)::period::den};

   long double time_taken_s{static_cast<long double>(ticks_taken.count()) / tick_interval};
   long double time_taken_m{time_taken_s / 60.0L};
   long double time_taken_h{time_taken_s / 3600.0L};
   long double time_taken_d{time_taken_s / 86400.0L};

   long double rand_rate{static_cast<long double>(M * TRIALS) / time_taken_s};
   long double trial_rate{static_cast<long double>(TRIALS) / time_taken_s};

   vector<my_uint_t> sizes;
   vector<long double> variances;
   vector<long double> means;

   for (const stats_t &stats : thread_results)
   {
      // TODO: Add any extra trials for the last thread
      sizes.push_back(NUM_THREADS);
      variances.push_back(stats.variance);
      means.push_back(stats.mean);
   }

   long double average_k{combined_mean_n(sizes, means)};
   long double variance{combined_variance_n(sizes, variances, means)};
   long double stddev{sqrt(variance)};
   long double std_err{stddev / sqrt(static_cast<long double>(TRIALS))};

   cout << "Expected average k: " << fixed << setprecision(10) << mth_harmonic(M) << endl;

   cout << "Actual average k  : "
        << fixed << setprecision(10)
        << average_k
        << " +/- " << std_err
        << endl;

   cout << endl;

   if (time_taken_s < 60.0L)
      cout << "Time taken              : " << fixed << setprecision(2) << time_taken_s << " seconds" << endl;
   else if (time_taken_s < 3600.0L)
      cout << "Time taken              : " << fixed << setprecision(2) << time_taken_m << " minutes" << endl;
   else if (time_taken_s < 86400.0L)
      cout << "Time taken              : " << fixed << setprecision(2) << time_taken_h << " hours" << endl;
   else
      cout << "Time taken              : " << fixed << setprecision(2) << time_taken_d << " days" << endl;

   cout << "Rand num generation rate: " << fixed << setprecision(0) << rand_rate << " / s" << endl;
   cout << "Trial rate              : " << fixed << setprecision(0) << trial_rate << " / s" << endl;

   cout << endl;
}
