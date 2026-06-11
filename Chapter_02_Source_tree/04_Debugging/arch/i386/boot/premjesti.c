
#include <types/basic.h>

#define VALUE 0xAB

#define P1ADDR 0x300000
#define P1SIZE 0x1000
#define P2ADDR 0x310000
#define P2SIZE 0x0800
#define STACK_SIZE 0x1000

extern char DATA_ROM, DATA_RAM, DATA_size;
extern char BSS_ROM, BSS_RAM, BSS_size;
extern char TEXT_ROM, TEXT_RAM, TEXT_size;
extern char RODATA_ROM, RODATA_RAM, RODATA_size;



void just_copy(char *from, char *to, size_t size)
{
	for (size_t i = 0; i < size; i++)
		to[i] = from[i];
}

void premjesti()
{	just_copy(&RODATA_ROM, &RODATA_RAM, (size_t)&RODATA_size);
	just_copy(&DATA_ROM, &DATA_RAM, (size_t)&DATA_size);
	just_copy(&TEXT_ROM, &TEXT_RAM, (size_t)&TEXT_size);
	just_copy(&BSS_ROM, &BSS_RAM, (size_t)&BSS_size);


}

