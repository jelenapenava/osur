#include <stdio.h>
#include <pthread.h>
#include <errno.h>

static pthread_spinlock_t spin;
static int counter = 0;

static void busy(volatile int n)
{
    volatile int i;
    for (i = 0; i < n; i++) {
    }
}

static void* w1(void* arg)
{
    int ret;

    printf("w1: pthread_spin_lock\n");
    ret = pthread_spin_lock(&spin);
    if (ret != 0) {
        printf("w1: pthread_spin_lock nije uspio: %d\n", ret);
        return 0;
    }
    printf("w1: pthread_spin_lock uspjeh\n");

    busy(40000);

    counter++;
    printf("w1: counter=%d\n", counter);

    printf("w1: pthread_spin_unlock\n");
    ret = pthread_spin_unlock(&spin);
    if (ret != 0) {
        printf("w1: pthread_spin_unlock nije uspio: %d\n", ret);
        return 0;
    }
    printf("w1: pthread_spin_unlock uspjeh\n");

    return 0;
}

static void* w2(void* arg)
{
    int ret;


    printf("\tw2: pthread_spin_trylock\n");
    ret = pthread_spin_trylock(&spin);
    if (ret == 0) {
        printf("\tw2: pthread_spin_trylock uspjeh\n");
        printf("\tw2: pthread_spin_unlock nakon trylock\n");
        pthread_spin_unlock(&spin);
    } else {
        printf("\tw2: pthread_spin_trylock nije uspio, ret=%d\n", ret);
    }

    busy(500000);

    printf("\tw2: pthread_spin_lock\n");
    ret = pthread_spin_lock(&spin);
    if (ret != 0) {
        printf("\tw2: pthread_spin_lock nije uspio: %d\n", ret);
        return 0;
    }
    printf("\tw2: pthread_spin_lock uspjeh\n");

    counter++;
    printf("\tw2: counter=%d\n", counter);

    printf("\tw2: pthread_spin_unlock\n");
    ret = pthread_spin_unlock(&spin);
    if (ret != 0) {
        printf("\tw2: pthread_spin_unlock nije uspio: %d\n", ret);
        return 0;
    }
    printf("\tw2: pthread_spin_unlock uspjeh\n");

    return 0;
}

int spin_demo(void)
{
    pthread_t t1, t2;
    int ret;

    ret = pthread_spin_init(&spin, 0);
    if (ret != 0) {
        printf("pthread_spin_init failed: %d\n", ret);
        return 1;
    }
    printf("pthread_spin_init\n");

    ret = pthread_create(&t1, 0, w1, 0);
    if (ret != 0) {
        printf("pthread_create w1 failed: %d\n", ret);
        return 1;
    }

    ret = pthread_create(&t2, 0, w2, 0);
    if (ret != 0) {
        printf("pthread_create w2 failed: %d\n", ret);
        return 1;
    }

    pthread_join(t1, 0);
    pthread_join(t2, 0);

    printf("pthread_spin_destroy\n");
    ret = pthread_spin_destroy(&spin);
    if (ret != 0) {
        printf("pthread_spin_destroy failed: %d\n", ret);
        return 1;
    }

    printf("final counter=%d\n", counter);
    printf("spin_demo: done\n");
    return 0;
}