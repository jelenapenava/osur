#include <stdio.h>
#include <pthread.h>

static pthread_rwlock_t rw;
static int shared_value = 0;

static void busy(volatile int n)
{
	volatile int i;
	for (i = 0; i < n; i++) {
	}
}

static void* reader1(void* arg)
{
	(void)arg;

	printf("r1: prije rdlock\n");
	pthread_rwlock_rdlock(&rw);
	printf("r1: nakon rdlock\n");

	printf("r1: cita shared_value=%d\n", shared_value);

	printf("r1: prije unlock\n");
	pthread_rwlock_unlock(&rw);
	printf("r1: nakon unlock\n");


	printf("r1: prije rdlock 2\n");
	pthread_rwlock_rdlock(&rw);
	printf("r1: nakon rdlock 2\n");

	printf("r1: cita shared_value=%d\n", shared_value);
    busy(1000000);

	printf("r1: prije unlock 2\n");
	pthread_rwlock_unlock(&rw);
	printf("r1: nakon unlock 2\n");

	return 0;
}

static void* reader2(void* arg)
{
	(void)arg;

    busy(2000000);
	printf("r2: prije rdlock\n");
	pthread_rwlock_rdlock(&rw);
	printf("r2: nakon rdlock\n");

	printf("r2: cita shared_value=%d\n", shared_value);

	printf("r2: prije unlock\n");
	pthread_rwlock_unlock(&rw);
	printf("r2: nakon unlock\n");

	return 0;
}

static void* writer(void* arg)
{
	(void)arg;

    busy(100000);
	printf("\tw: prije wrlock\n");
	pthread_rwlock_wrlock(&rw);
	printf("\tw: nakon wrlock\n");

	shared_value++;
	printf("\tw: upisao shared_value=%d\n", shared_value);


	printf("\tw: prije unlock\n");
	pthread_rwlock_unlock(&rw);
	printf("\tw: nakon unlock\n");

	return 0;
}

int rwlock_demo(void)
{
	pthread_t r1, r2, w;

	pthread_rwlock_init(&rw, 0);

	pthread_create(&r1, 0, reader1, 0);
   
	pthread_create(&w, 0, writer, 0);
	pthread_create(&r2, 0, reader2, 0);


	pthread_join(r1, 0);
	pthread_join(r2, 0);
	pthread_join(w, 0);

	pthread_rwlock_destroy(&rw);

	printf("rwlock_demo: done\n");
	return 0;
}