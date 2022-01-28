// Reference: https://elixir.bootlin.com/glibc/latest/source/nptl/pthread_spin_lock.c
#define _GNU_SOURCE
#include <atomic.h>
#include <shlib-compat.h>

#include "pthreadP.h"

int __pthread_spin_lock(pthread_spinlock_t *lock) {
    int val = 0;

    /* We assume that the first try mostly will be successful, thus we use
     atomic_exchange if it is not implemented by a CAS loop (we also assume
     that atomic_exchange can be faster if it succeeds, see
     ATOMIC_EXCHANGE_USES_CAS).  Otherwise, we use a weak CAS and not an
     exchange so we bail out after the first failed attempt to change the
     state.  For the subsequent attempts we use atomic_compare_and_exchange
     after we observe that the lock is not acquired.
     See also comment in pthread_spin_trylock.
     We use acquire MO to synchronize-with the release MO store in
     pthread_spin_unlock, and thus ensure that prior critical sections
     happen-before this critical section.  */
#if !ATOMIC_EXCHANGE_USES_CAS
    /* Try to acquire the lock with an exchange instruction as this architecture
     has such an instruction and we assume it is faster than a CAS.
     The acquisition succeeds if the lock is not in an acquired state.  */
    // if (lock == 0) return 0;
    // if (lock == 1) swap two value, return old value.
    if (__glibc_likely(atomic_exchange_acquire(lock, 1) == 0))  // GNU lib
        return 0;
#else
    /* Try to acquire the lock with a CAS instruction as this architecture
     has no exchange instruction.  The acquisition succeeds if the lock is not
     acquired.  */
    /* Assume that the spin lock will often lock successfully */
    if (__glibc_likely(atomic_compare_exchange_weak_acquire(lock, &val, 1)))
        return 0;
#endif

    do {
        /* The lock is contended and we need to wait.  Going straight back
	 to cmpxchg is not a good idea on many targets as that will force
	 expensive memory synchronizations among processors and penalize other
	 running threads.
	 There is no technical reason for throwing in a CAS every now and then,
	 and so far we have no evidence that it can improve performance.
	 If that would be the case, we have to adjust other spin-waiting loops
	 elsewhere, too!
	 Thus we use relaxed MO reads until we observe the lock to not be
	 acquired anymore.  */
        do {
            /* TODO Back-off.  */
            // Back off is an algorithm such that every thread wait for a distinct short time.

            atomic_spin_nop();  // in x86, same as asm("pause"); we don't want CPU overheating

            val = atomic_load_relaxed(lock);
        } while (val != 0);  // spend less time here

        /* We need acquire memory order here for the same reason as mentioned
	 for the first try to lock the spinlock.  */
    } while (!atomic_compare_exchange_weak_acquire(lock, &val, 1));  // spend more time here.

    return 0;
}
versioned_symbol(libc, __pthread_spin_lock, pthread_spin_lock, GLIBC_2_34);

#if OTHER_SHLIB_COMPAT(libpthread, GLIBC_2_2, GLIBC_2_34)
compat_symbol(libpthread, __pthread_spin_lock, pthread_spin_lock, GLIBC_2_2);
#endif

int __pthread_spin_unlock(pthread_spinlock_t *lock) {
    /* The atomic_store_release synchronizes-with the atomic_exchange_acquire
     or atomic_compare_exchange_weak_acquire in pthread_spin_lock /
     pthread_spin_trylock.  */
    atomic_store_release(lock, 0);
    return 0;
}
versioned_symbol(libc, __pthread_spin_unlock, pthread_spin_unlock,
                 GLIBC_2_34);

#if OTHER_SHLIB_COMPAT(libpthread, GLIBC_2_2, GLIBC_2_34)
compat_symbol(libpthread, __pthread_spin_unlock, pthread_spin_unlock,
              GLIBC_2_2);
#endif