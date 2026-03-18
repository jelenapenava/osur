#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generator.h"

int generiraj(char *buffer, size_t size)
{
	size_t velicina = size/2 + random() % (size/2);
	int i;

	for (i = 0; i < velicina; i++)
		buffer[i] = 33 + random() % (126-33); //"printable ascii"

	return velicina;
}