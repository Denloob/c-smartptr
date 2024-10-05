#include "autoptr.h"
#include <pthread.h>
#include <stdio.h>

int main()
{
    // `mutex` is not a pointer, however pthread_mutex_destroy needs a
    // pointer. Thus we use autoptr_func_ptr.
    autoptr_func_ptr(pthread_mutex_destroy) pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    {
        puts("Locking...");
        pthread_mutex_lock(&mutex);

#if 1
        defer({
            puts("Unlocking...");
            pthread_mutex_unlock(*(void **)ptr);
        }, &mutex);
#else
        // If you only wish to unlock, you can use defer_func
        defer_func(pthread_mutex_unlock, &mutex);
#endif

        // Critical section
        puts("Critical section");

        // Mutex auto unlocked here
    }

    puts("Hi!");
}
