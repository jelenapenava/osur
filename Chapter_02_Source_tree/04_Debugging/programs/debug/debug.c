/*! Simple program prepared for little debugging */

#include <stdio.h>
#include <api/prog_info.h>
#include <api/errno.h>
#include <kernel/errno.h>

static int inc(int n)
{
	n++;

	return n;
}
static int x=5;
static int y;

extern char p1[];
extern char p2[];


int debug()
{
	int a, b, c;

	printf("Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 debug_PROG_HELP);

	a = 1;

	b = a + 1;

	c = inc(a) + inc(b);

	a += b + c;
	b += a + c;
	c += a + b;

	printf("a=%d, b=%d, c=%d\n", a, b, c);

#if 1	/* compile with 'debug=yes' and without */
	//LOG(WARN, "This is log entry with WARN relevance");
	//LOG(INFO, "Address of 'a' is %x", &a);

	void k_startup();
	extern char system_info[];

	printf("\n");
	LOG(INFO, " k_startup (CODE) is at %x", k_startup);
	LOG(INFO, " debug (CODE) is at    %x", debug);

	printf("\n");
	LOG(INFO, " startup (DATA) is at   %x", system_info);
	LOG(INFO, " x (DATA) is at        %x", &x);
	printf("\n");
	LOG(INFO, " y (BSS ) is at        %x", &y);
	printf("\n");
	LOG(INFO, " a (STACK) is at   %x", &a);
	LOG(INFO, " b (STACK) is at   %x", &b);
	LOG(INFO, " c (STACK) is at   %x", &c);
	printf("\n");

	LOG(INFO, "p1 region start              %x", &p1);
	LOG(INFO, "p1[2] char '%c' at %x", p1[2], &p1[2]);
	LOG(INFO, "p2 region start              %x", &p2);
	LOG(INFO, "p2[2] char '%c' at %x", p2[2], &p2[2]);



	ASSERT_ERRNO_AND_RETURN(TRUE, EINVAL);

	ASSERT(TRUE);
	//ASSERT(FALSE);
#endif
	return 0;
}
