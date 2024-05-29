#ifndef THREAD_MAIN_INCLUDED
#define THREAD_MAIN_INCLUDED

#include <cstddef>

using namespace std;

#include "fundamental_types.h"
struct stats_t
{
   long double mean{0.0L};
   long double variance{0.0L};
};

stats_t thread_main();

#endif
