#ifndef THREAD_MAIN_INCLUDED
#define THREAD_MAIN_INCLUDED

#include <cstddef>

using namespace std;

#include "fundamental_types.h"
struct stats_t
{
   // TODO: Add count of data points
   long double mean{0.0L};
   long double variance{0.0L};
};

//TODO: Add trial count back as parameter
stats_t thread_main();

#endif
