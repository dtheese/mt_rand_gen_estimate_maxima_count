#include <cassert>
#include <cmath>
#include <cstddef>

using namespace std;

#include "utilities.h"

long double combined_mean(
                            my_uint_t x_n,
                            long double x_bar,

                            my_uint_t y_n,
                            long double y_bar
                         )
{
   long double x_n_ld{static_cast<long double>(x_n)};
   long double y_n_ld{static_cast<long double>(y_n)};

   return (x_n_ld*x_bar + y_n_ld*y_bar) / (x_n_ld + y_n_ld);
}

long double combined_mean_n(
                              const vector<my_uint_t> &sizes,
                              const vector<long double> &means
                           )
{
   size_t num_sets{sizes.size()};

   assert(num_sets > 0);
   assert(num_sets == means.size());

   my_uint_t size_combined{sizes[0]};
   long double mean_combined{means[0]};

   for (size_t i{1}; i < num_sets; ++i)
   {
      my_uint_t this_size{sizes[i]};
      long double this_mean{means[i]};

      mean_combined = combined_mean(
                                      size_combined,
                                      mean_combined,

                                      this_size,
                                      this_mean
                                   );

      size_combined += this_size;
   }

   return mean_combined;
}

long double combined_variance(
                                my_uint_t x_n,
                                long double x_V,
                                long double x_bar,

                                my_uint_t y_n,
                                long double y_V,
                                long double y_bar
                             )
{
   long double x_n_ld{static_cast<long double>(x_n)};
   long double y_n_ld{static_cast<long double>(y_n)};

   return (
             ((x_n_ld - 1.0L)*x_V + (y_n_ld - 1.0L)*y_V) /
             (x_n_ld + y_n_ld - 1.0L)
          ) +
          (
             x_n_ld*y_n_ld*pow(x_bar - y_bar, 2.0L) /
             ((x_n + y_n)*(x_n + x_V - 1.0L))
          );
}

long double combined_variance_n(
                                  const vector<my_uint_t> &sizes,
                                  const vector<long double> &variances,
                                  const vector<long double> &means
                               )
{
   size_t num_sets{sizes.size()};

   assert(num_sets > 0);
   assert(num_sets == variances.size());
   assert(num_sets == means.size());

   my_uint_t size_combined{sizes[0]};
   long double variance_combined{variances[0]};
   long double mean_combined{means[0]};

   for (size_t i{1}; i < num_sets; ++i)
   {
      my_uint_t this_size{sizes[i]};
      long double this_variance{variances[i]};
      long double this_mean{means[i]};

      variance_combined = combined_variance(
                                              size_combined,
                                              variance_combined,
                                              mean_combined,

                                              this_size,
                                              this_variance,
                                              this_mean
                                           );

      mean_combined = combined_mean(
                                      size_combined,
                                      mean_combined,

                                      this_size,
                                      this_mean
                                   );

      size_combined += this_size;
   }

   return variance_combined;
}

long double mth_harmonic(my_uint_t m)
{
   // This is an approximation to the mth harmonic number. This
   // approximation is good to two decimal places for the worst
   // case of m = 1. The accuracy then grows quickly as m increases.
   long double m_ld{static_cast<long double>(m)};

   long double rval{
                      log(m_ld) +
                      0.5772156649L +
                      1.0L / (2.0L * m_ld) -
                      1.0L / (12.0L * pow(m_ld, 2.0L)) +
                      1.0L / (120.0L * pow(m_ld, 4.0L))
                   };

   return rval;
}
