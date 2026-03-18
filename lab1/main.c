#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "postavke.h"
#include "ulaz/ulaz.h"
#include "obrada/obrada.h"
#include "izlaz/izlaz.h"

#define MS_SIZE	 10240   //10 KB, povecati ako treba

int main()
{
	char ms_ulaz[MS_SIZE], ms_izlaz[MS_SIZE];
	int ul_vel, izl_vel, status;
	int nacin_ulaza, nacin_obrade, nacin_izlaza;

	srandom((unsigned) getpid() + time(NULL));

	nacin_ulaza = ZASTAVICA(UCITAJ_IZ_DATOTEKE);
	//nacin_ulaza = ZASTAVICA(UCITAJ_IZ_DATOTEKE + random() % 3);
	ul_vel = ucitaj(ms_ulaz, MS_SIZE, nacin_ulaza);
	if (ul_vel <= 0) {
		fprintf(stderr, "Ulaz nije nista generirao!\n");
		return -1;
	}

	//nacin_obrade = ZASTAVICA(OBRADI_POBROJI * random() % 2); //koristiti ili ne obradu "pobroji"
	//nacin_obrade += ZASTAVICA(OBRADI_SMISAO * random() % 2); //koristiti ili ne složenije obrade
	nacin_obrade = ZASTAVICA(OBRADI_POBROJI);
	nacin_obrade += ZASTAVICA(OBRADI_SMISAO);
	if ((nacin_obrade & ZASTAVICA(OBRADI_SMISAO))) {
		//nacin_obrade += ZASTAVICA(OBRADI_SMISAO_NA_BRZINU + random() % 2);
		nacin_obrade += ZASTAVICA(OBRADI_SMISAO_DUBLJE);
	}
	izl_vel = obradi(ms_ulaz, ul_vel, nacin_obrade, ms_izlaz, MS_SIZE);
	if (izl_vel <= 0){
		fprintf(stderr, "Obrada nije dala nista korisno!\n");
		return -1;
	}

	//nacin_izlaza = ZASTAVICA(SPREMI_U_DATOTEKU + random() % 2);
	nacin_izlaza = ZASTAVICA(SPREMI_U_DATOTEKU);
	status = spremi(ms_izlaz, izl_vel, nacin_izlaza);
	if (status <= 0){
		fprintf(stderr, "Greska pri spremanju rezultata!\n");
		return -1;
	}
	
	return 0;
}