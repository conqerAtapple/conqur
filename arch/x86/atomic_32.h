#ifndef _atomic_32_h
#define _atomic_32_h

typedef int spinlock_t;

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

#define SPIN_LOCK_YIELD


#endif
