#include "globals.h"
#include "prng.h"
#include "thread_main.h"

stats_t thread_main(my_uint_t thread_trials)
{
   long double old_mean{0.0L};
   long double old_variance{0.0L};

   prng_t<my_uint_t, 1, N> prng;
   stats_t rval;

   for (my_uint_t trial{1}; trial <= thread_trials; ++trial)
   {
      my_uint_t max_seen{0};
      my_uint_t k{0};

      for (my_uint_t m{0}; m < M; ++m)
      {
         my_uint_t one_num{prng.rand()};

         if (one_num > max_seen)
         {
            max_seen = one_num;
            ++k;
         }
      }

      long double k_ld{static_cast<long double>(k)};

      if (trial == 1)
      {
         rval.mean = k_ld;
         old_mean = k_ld;
         old_variance = 0.0L;
      }
      else
      {
         rval.mean = old_mean + (k_ld - old_mean) / static_cast<long double>(trial);
         rval.variance = old_variance + (k_ld - old_mean) * (k_ld - rval.mean);
         old_mean = rval.mean;
         old_variance = rval.variance;
      }
   }

   rval.variance /= static_cast<long double>(thread_trials - 1);

   return rval;
}
