#ifndef COMPILER_H_
#define COMPILER_H_

#include "archtypes.h"

#define ALIGNED_CACHELINE __attribute__((aligned(L1_CACHE_BYTES)))

#endif
