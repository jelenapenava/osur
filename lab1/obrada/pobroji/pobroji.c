#include <stdio.h>
#include <string.h>
#include "pobroji.h"

int pobroji(char *ulaz, size_t vel_ulaza, char *izlaz, size_t vel_izlaza)
{
	int znakova = strlen(ulaz);
	int rijeci = 0, i, max;
	char bufer[64];

	for (i = 0; ulaz[i] != '\0'; i++) {
		if ((ulaz[i] == ' ' || ulaz[i] == '\t' || ulaz[i] == '\n') && (ulaz[i+1] != ' ' && ulaz[i+1] != '\t' && ulaz[i+1] != '\n'))
			rijeci++;    
	}
	if (ulaz[i-1] != ' ' && ulaz[i-1] != '\t' && ulaz[i-1] != '\n')
		rijeci++;    

	sprintf(bufer, "znakova=%d\nrijeci=%d\n", znakova, rijeci);
	max = strlen(bufer);
	if (max > vel_izlaza)
		max = vel_izlaza;
	memset(izlaz, 0, vel_izlaza);
	strncpy(izlaz, bufer, max);
	
	return max;
}