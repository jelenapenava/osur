#include <stdio.h>
#include <string.h>
#include "tipkovnica.h"

int ucitaj_s_tipkovnice(char *ms, size_t size)
{
	printf("Unesi ulaz s tipkovnice (do %d znakova): ", (int) size);
	fgets(ms, size, stdin);

	return strlen(ms);
}