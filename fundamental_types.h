#ifndef FUNDAMENTAL_TYPES_INCLUDED
#define FUNDAMENTAL_TYPES_INCLUDED

#include <type_traits>

using namespace std;

// Don't use uint64_t since it is not (officially) supported by
// uniform_int_distribution<>.
using my_uint_t = unsigned long long;

static_assert(
                sizeof(my_uint_t) == 8 &&
                is_integral_v<my_uint_t> &&
                is_unsigned_v<my_uint_t>,
                "my_uint_t must be a 64-bit unsigned integer type"
             );

#endif
