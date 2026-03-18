#include <stdio.h>
#include <string.h>

#include "dublje.h"
#include "../smisao.h"
#include "../../../postavke.h"

#define MAXITEM		50

extern char *rijecnik[BR_RIJECI];

int smisao_dublje(char *ulaz, size_t vel_ulaza, char *izlaz, size_t vel_izlaza)
{
	int i, broj = 0, rb, mjesta = vel_izlaza, v;
	char ms[MAXITEM], *tmp;

	memset(izlaz, 0, vel_izlaza);
	for (i = 0; i < BR_RIJECI; i++) {
		if (strstr(ulaz, rijecnik[i]) != NULL) {
			broj++;
			rb = 1;
			tmp = ulaz;
			while ((tmp = strstr(tmp, rijecnik[i])) != NULL) {
				rb++;
				tmp += strlen(rijecnik[i]);
			}
			memset(ms, 0, MAXITEM);
			sprintf(ms, "rijec '%s' se pojavljuje %d puta\n", rijecnik[i], rb);
			v = strlen(ms);
			if (v <= vel_izlaza) {
				strncat(izlaz, ms, v);
				vel_izlaza -= v;
			}
			else break;
		}
	}
	memset(ms, 0, MAXITEM);
	sprintf(ms, "ukupno rijeci: %d\n", broj);
	v = strlen(ms);
	if (v <= vel_izlaza) {
		strncat(izlaz, ms, v);
		vel_izlaza -= v;
	}
	return strlen(izlaz);
}