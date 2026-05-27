#include <stdio.h>
#include <pthread.h>

static sem_t sem;

static void busy(volatile int n)
{
	volatile int i;
	for (i = 0; i < n; i++) {
	}
}


static void *worker(void *arg)
{
	printf("\tsem_wait_x(5)\n");
	sem_wait_x(&sem, 5);
	printf("\toslobodeno\n");
	return NULL;
}

int lab5x(void)
{
	pthread_t t;

	sem_init(&sem, 0, 2);

	printf("sem init 2\n");

	pthread_create(&t, NULL, worker, NULL);
	busy(1000000);

	printf("sem dodajemo 2\n");
	sem_post(&sem);
    sem_post(&sem);
    sem_post(&sem);
	busy(1000000);

	printf("sem dodajemo 1\n");
	sem_post(&sem);

	pthread_join(t, NULL);

	printf("lab5x done\n");
	return 0;
}