#include <stdio.h>
#include <string.h>

#include "datoteka.h"
#include "../../postavke.h"

int spremi_u_datoteku(char *rezultat, size_t velicina)
{
	int status;
	FILE *fp = fopen(DATOTEKA_IZLAZ, "w");

	if (fp == NULL) {
		fprintf(stderr, "Greska u otvaranju datoteke %s", DATOTEKA_IZLAZ);
		perror("");
		status = -1;
	}
	else {
		status = fwrite(rezultat, velicina, 1, fp);
	}
	return status;
}