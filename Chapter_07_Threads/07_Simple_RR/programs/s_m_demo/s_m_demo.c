#include <stdio.h>
#include <pthread.h>

static sem_t sem;
static pthread_mutex_t mtx;

static void busy(volatile int n)
{
	volatile int i;
	for (i = 0; i < n; i++) {
	}
}

static void* hold(void* arg)
{
	(void)arg;

	if (sem_wait(&sem) != 0) {
		printf("sem_wait failed\n");
		return 0;
	}

	if (pthread_mutex_lock(&mtx) != 0) {
		printf("mutex_lock failed\n");
		sem_post(&sem);
		return 0;
	}

	printf("zauzet semafor i mutex\n");

	busy(6000000);

	sem_post(&sem);
	printf("osloboden semafor, mutex jos drzi\n");

	busy(3000000);

	pthread_mutex_unlock(&mtx);
	printf("osloboden i mutex\n");

	return 0;
}

static void* tester(void* arg)
{
	(void)arg;
	int i;

	for (i = 0; i < 6; i++) {
		busy(3000000);

		if (sem_trywait(&sem) == 0) {
			printf("\tsem_trywait uspio u krugu %d\n", i);
			sem_post(&sem);
		} else {
			printf("\tsem_trywait nije uspio u krugu %d\n", i);
		}

		if (pthread_mutex_trylock(&mtx) == 0) {
			printf("\tpthread_mutex_trylock uspio u krugu %d\n", i);
			pthread_mutex_unlock(&mtx);
		} else {
			printf("\tpthread_mutex_trylock nije uspio u krugu %d\n", i);
		}
	}

	return 0;
}

int s_m_demo(void)
{
	pthread_t t1, t2;

	sem_init(&sem, 0, 1);
	pthread_mutex_init(&mtx, 0);

	pthread_create(&t1, 0, hold, 0);
	pthread_create(&t2, 0, tester, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);

	return 0;
}