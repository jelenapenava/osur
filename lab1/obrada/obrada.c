#include <stdio.h>
#include <string.h>

#include "obrada.h"
#include "pobroji/pobroji.h"
#include "smisao/smisao.h"
#include "../postavke.h"

int obradi(char *ulaz, size_t vel_ulaza, int kako, char *izlaz, size_t vel_izlaza)
{
	size_t velicina_rezultata1 = 0, velicina_rezultata2 = 0;
	
	if ((kako & ZASTAVICA(OBRADI_POBROJI)))
		velicina_rezultata1 = pobroji(ulaz, vel_ulaza, izlaz, vel_izlaza);

	if ((kako & ZASTAVICA(OBRADI_SMISAO)))
		velicina_rezultata2 = smisao(ulaz, vel_ulaza, kako, izlaz + velicina_rezultata1, vel_izlaza - velicina_rezultata1);
	
	#if DEBUG == 1
	printf("\nizlaz:\n______\n%s\n", izlaz);
	#endif

	return strlen(izlaz);
}