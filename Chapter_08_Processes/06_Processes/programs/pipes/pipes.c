
#include <api/pthread.h>
#include <api/stdio.h>
#include <api/syscall.h>
#include <api/errno.h>
#include <time.h>


char PROG_HELP[] = "Pipes example.";
#define PIPE1 "C1"
#define PIPE2 "C2"

/* ------------------------------------------------------------------ */
/* P2: writer to C1                                                   */
/* ------------------------------------------------------------------ */
static struct timespec sleep_time = {.tv_sec = 1, .tv_nsec = 0};

static void msleep(int sec)
{
    sleep_time.tv_sec = sec;
    sleep_time.tv_nsec = 0;
    nanosleep(&sleep_time, NULL);
}
void *p2_main(void *arg)
{
	int c1 = pipe_open(PIPE1, 10);

	if (c1 < 0)
	{
		printf("P2: pipe_open C1 failed\n");
		return 0;
	}

	while (1)
	{
		pipe_write(c1, "abcdef", 6);
		printf("P2 -> C1: abcdef\n");

		msleep(5);
	}

	return 0;
}

/* ------------------------------------------------------------------ */
/* P3: read C1 + write C2                                             */
/* ------------------------------------------------------------------ */

void *p3_main(void *arg)
{
	int c1 = pipe_open(PIPE1, 10);
	int c2 = pipe_open(PIPE2, 20);


	if (c1 < 0 || c2 < 0)
	{
		printf("P3: pipe_open failed\n");
		return 0;
	}
	printf("P3 alive\n");
	while (1)
	{
		char buf[5];

		int n = pipe_read(c1, buf, 5);

		if (n > 0)
		{
			printf("P3 <- C1: ");
			write(1, buf, n);
			printf("\n");
		}

		pipe_write(c2, "ABCDEFG", 7);
		printf("P3 -> C2: ABCDEFG\n");

		msleep(5);
	}

	return 0;
}

/* ------------------------------------------------------------------ */
/* P1: main controller                                                */
/* ------------------------------------------------------------------ */


int pipes()
{
	int c1 = pipe_open(PIPE1, 10);
	int c2 = pipe_open(PIPE2, 20);

	if (c1 < 0 || c2 < 0)
	{
		printf("P1: pipe_open failed\n");
		return -1;
	}

	printf("P1: pipes created\n");

	/* spawn P2 */
	pthread_t t2;
	pthread_create(&t2, NULL, p2_main, NULL);

	/* spawn P3 */
	pthread_t t3;
	pthread_create(&t3, NULL, p3_main, NULL);

	while (1)
	{
		/* send data to C1 */
		pipe_write(c1, "123456", 6);
		printf("P1 -> C1: 123456\n");

		/* read 10 bytes from C2 */
		char buf[10];
		int total = 0;

		while (total < 10)
		{
			int n = pipe_read(c2, buf + total, 10 - total);

			if (n > 0)
				total += n;
		}

		printf("P1 <- C2: ");
		write(1, buf, 10);
		printf("\n");

		msleep(1);
	}

	return 0;
}