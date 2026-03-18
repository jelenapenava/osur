#include <stdio.h>
#include <string.h>
#include "datoteka.h"
#include "../../postavke.h"

int ucitaj_iz_datoteke(char *ms, size_t size)
{
	int velicina;
	FILE *fp = fopen(DATOTEKA_ULAZ, "r");

	if (fp == NULL) {
		fprintf(stderr, "Greska u otvaranju datoteke %s", DATOTEKA_ULAZ);
		perror("");
		velicina = -1;
	}
	else {
		char *p = ms;
		size_t s = size, n;
		while (fgets(p, s, fp)) {
			n = strlen(p);
			p += n;
			s -= n;
		}
	}
	return strlen(ms);
}