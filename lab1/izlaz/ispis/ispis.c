#include <stdio.h>

#include "ispis.h"
#include "../../postavke.h"

int ispisi_na_zaslon(char *rezultat, size_t velicina)
{
	printf("Projekt %s (autor %s)\n", PROJEKT, AUTOR);
	printf("Rezultat:\n%.*s", (int) velicina, rezultat);

	return velicina;
}