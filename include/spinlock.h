#ifndef SPLINLOCK_H
#define SPLINLOCK_H

#include "atomic.h"

//
//TODO: convert to c++ class
//

#define SPINS_PER_YIELD 63

static int spinlock(spinlock_t *sl) 
{
    int spins = 0;
    while (*(volatile int *)sl != 0 || cas_lock(sl))
    {
        if ((++spins & SPINS_PER_YIELD) == 0)
        {
            SPIN_LOCK_YIELD;
        }
    }
    return 0;
}

#endif

