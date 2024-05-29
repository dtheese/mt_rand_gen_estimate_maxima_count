#ifndef UTILITIES_INCLUDED
#define UTILITIES_INCLUDED

#include <vector>

using namespace std;

#include "fundamental_types.h"

// Given two sample sets x and y, this function returns the mean
// of the union of the two sets. No data points from either set are
// needed. The needed input is:
// x_n, y_n: The size of sets x and y
// x_bar, y_bar: The means of sets x and y
long double combined_mean(
                            my_uint_t x_n,
                            long double x_bar,

                            my_uint_t y_n,
                            long double y_bar
                         );

// Given n sample sets, this function returns the mean
// of the union of those sets. No data points from any set are
// needed. The needed input is:
// sizes: A vector<> containg the size of each set
// means: A vector<> containing the mean of each set
long double combined_mean_n(
                              const vector<my_uint_t> &sizes,
                              const vector<long double> &means
                           );

// Given two sample sets x and y, this function returns the variance
// of the union of the two sets. No data points from either set are
// needed. The needed input is:
// x_n, y_n: The size of sets x and y
// x_V, y_V: The variance of sets x and y
// x_bar, y_bar: The means of sets x and y
long double combined_variance(
                                my_uint_t x_n,
                                long double x_V,
                                long double x_bar,

                                my_uint_t y_n,
                                long double y_V,
                                long double y_bar
                             );

// Given n sample sets, this function returns the variance
// of the union of those sets. No data points from any set are
// needed. The needed input is:
// sizes: A vector<> containg the size of each set
// variances: A vector<> containing the variance of each set
// means: A vector<> containing the mean of each set
long double combined_variance_n(
                                  const vector<my_uint_t> &sizes,
                                  const vector<long double> &variances,
                                  const vector<long double> &means
                               );

long double mth_harmonic(my_uint_t m);

#endif
