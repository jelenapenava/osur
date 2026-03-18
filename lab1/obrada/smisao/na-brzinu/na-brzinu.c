#include <stdio.h>
#include <string.h>

#include "na-brzinu.h"
#include "../smisao.h"
#include "../../../postavke.h"

#define MAXITEM		32

extern char *rijecnik[BR_RIJECI];

int smisao_na_brzinu(char *ulaz, size_t vel_ulaza, char *izlaz, size_t vel_izlaza)
{
	int i, broj = 0, mjesta = vel_izlaza, v;
	char ms[MAXITEM];

	memset(izlaz, 0, vel_izlaza);
	for (i = 0; i < BR_RIJECI; i++) {
		if (strstr(ulaz, rijecnik[i]) != NULL) {
			broj++;
			memset(ms, 0, MAXITEM);
			sprintf(ms, "ima rijeci: %s\n", rijecnik[i]);
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