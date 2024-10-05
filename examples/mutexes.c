#include "smartptr.h"
#include <pthread.h>
#include <stdio.h>

int main()
{
    // `mutex` is not a pointer, however pthread_mutex_destroy needs a
    // pointer. Thus we use smartptr_func_ptr.
    smartptr_func_ptr(pthread_mutex_destroy) pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    {
        puts("Locking...");
        pthread_mutex_lock(&mutex);

        defer({
            puts("Unlocking...");
            pthread_mutex_unlock(&mutex);
        });

        // Critical section
        puts("Critical section");

        // Mutex auto unlocked here
    }

    puts("Hi!");
}
