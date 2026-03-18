#include <stdio.h>

#include "izlaz.h"
#include "datoteka/datoteka.h"
#include "ispis/ispis.h"
#include "../postavke.h"

int spremi(char *rezultat, size_t velicina, int kamo)
{
	int status = 0;

	if ((kamo & ZASTAVICA(SPREMI_U_DATOTEKU)))
		status = spremi_u_datoteku(rezultat, velicina);
	
	if ((kamo & ZASTAVICA(ISPISI_NA_ZASLON)))
		status = ispisi_na_zaslon(rezultat, velicina);
	
	return status;
}