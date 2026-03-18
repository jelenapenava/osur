#include <stdio.h>

#include "smisao.h"
#include "na-brzinu/na-brzinu.h"
#include "dublje/dublje.h"
#include "../../postavke.h"

char *rijecnik[BR_RIJECI] = RIJECI;

int smisao(char *ulaz, size_t vel_ulaza, int kako, char *izlaz, size_t vel_izlaza)
{
	if ((kako & ZASTAVICA(OBRADI_SMISAO_NA_BRZINU)))
		return smisao_na_brzinu(ulaz, vel_ulaza, izlaz, vel_izlaza);
	else if ((kako & ZASTAVICA(OBRADI_SMISAO_DUBLJE)))
		return smisao_dublje(ulaz, vel_ulaza, izlaz, vel_izlaza);
}