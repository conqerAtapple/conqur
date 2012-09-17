#ifndef _ATOMIC_32_H
#define _ATOMIC_32_H

typedef int spinlock_t;
typedef int atomic_t;

#define cas(ptr, old, new) \
({  \
    unsigned long  __ret;                                                                       \
    unsigned long  __new = reinterpret_cast<unsigned long>(new); \
    unsigned long  __old = reinterpret_cast<unsigned long>(old);     \
    volatile unsigned long *__ptr = (volatile unsigned long *)(ptr);      \
    asm volatile( "lock cmpxchgl %2,%1"                                               \
			     : "=a" (__ret), "+m" (*__ptr)      \
                 : "r" (__new), "0" (__old)            \
                 : "memory");                           \
                 (__ret == __old) ; \
})



#if defined(__GNUC__)&& (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
    #define cas_lock(sl)     __sync_lock_test_and_set(sl, 1)
    #define clear_lock(sl)   __sync_lock_release(sl)

#elif (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
/* Custom spin locks for older gcc on x86 */
static inline int x86_cas_lock(int *sl) {
    int ret;
    int val = 1;
    int cmp = 0;
    __asm__ __volatile__  ("lock; cmpxchgl %1, %2"
                           : "=a" (ret)
                           : "r" (val), "m" (*(sl)), "0"(cmp)
                           : "memory", "cc");
    return ret;
}

static inline void x86_clear_lock(int* sl) {
    assert(*sl != 0);
    int prev = 0;
    int ret;
    __asm__ __volatile__ ("lock; xchgl %0, %1"
                          : "=r" (ret)
                          : "m" (*(sl)), "0"(prev)
                          : "memory");
}

    #define cas_lock(sl)     x86_cas_lock(sl)
    #define clear_lock(sl)   x86_clear_lock(sl)

#endif

static inline atomic_t atomic_get(atomic_t *v)
{
    return(*(volatile int *)v);
}

static inline void atomic_dec(atomic_t *v)
{
    asm volatile( "lock;decl %0"
                  : "+m" (*v));
}

static inline void atomic_inc(atomic_t *v)
{
    asm volatile( "lock;incl %0"
                  : "+m" (*v));
}


static inline bool atomic_dec_and_test(atomic_t *v)
{
    unsigned char c;
    asm volatile( "lock;decl %0; sete %1"
                  : "+m" (*v), "=qm" (c)
                  : : "memory");
    return c != 0;
}

#define SPIN_LOCK_YIELD


#endif
