#include <stdio.h>

#include "ulaz.h"
#include "../postavke.h"
#include "datoteka/datoteka.h"
#include "generator/generator.h"
#include "tipkovnica/tipkovnica.h"

int ucitaj(char *ulaz, size_t max_vel, int od_kuda)
{
	size_t velicina = 0;
	
	if ((od_kuda & ZASTAVICA(UCITAJ_IZ_DATOTEKE)))
		velicina = ucitaj_iz_datoteke(ulaz, max_vel);
	else if ((od_kuda & ZASTAVICA(UCITAJ_S_TIPKOVNICE)))
		velicina = ucitaj_s_tipkovnice(ulaz, max_vel);
	else if ((od_kuda & ZASTAVICA(GENERIRAJ_ULAZ)))
		velicina = generiraj(ulaz, max_vel);

	#if DEBUG == 1
	printf("\nUlaz:\n______\n%s\n", ulaz);
	#endif

	return velicina;
}