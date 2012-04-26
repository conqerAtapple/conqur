#ifndef REFCOUNT_H
#define REFCOUNT_H

struct RefCount
{
    RefCount(atomic_t c):
    count(c)
    {
    }

    unsigned value()
    {
        return(atomic_get(&count));
    }

    void dec()
    {
        atomic_dec(&count);
    }

    void inc()
    {
       atomic_inc(&count);
    }

    bool decAndTest()
    {
       return (atomic_dec_and_test(&count));
    }

    atomic_t count;
};

#endif
