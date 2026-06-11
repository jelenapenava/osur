/*! linker script for memory layout */

/* Its parsed as C before used in linking! */


ENTRY(arch_startup)

SECTIONS {
	.boot LOAD_ADDR : AT(LOAD_ADDR) {
		* ?/boot/startup.asm.o
	}

	BOOT_size = SIZEOF(.boot);
	RODATA_ROM = BOOT_size + LOAD_ADDR;
	
	.rodata ADDR_DATA : AT(RODATA_ROM) {
		*.o(.rodata*)
		. = ALIGN (4096);

	}

	RODATA_size = SIZEOF(.rodata);
	RODATA_RAM =  ADDR_DATA;	
	DATA_ROM = RODATA_size + RODATA_ROM;
	DATA_RAM = RODATA_size + RODATA_RAM;

	.data DATA_RAM : AT(DATA_ROM) {
		*.o(.data*)
		. = ALIGN (4096);

	}

	DATA_size = SIZEOF(.data);
	TEXT_ROM = DATA_size + DATA_ROM;
	TEXT_RAM =  DATA_size + DATA_RAM;

	.text TEXT_RAM : AT(TEXT_ROM) {
		*.o(.text*)
		. = ALIGN (4096);

	}

	TEXT_size = SIZEOF(.text);

	BSS_ROM = TEXT_size + TEXT_ROM;
	BSS_RAM =  TEXT_size + TEXT_RAM;
	
	.bss BSS_RAM : AT(BSS_ROM){
		*.o(.bss*)
		. = ALIGN (4096);
	}
	BSS_size = SIZEOF(.bss);

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */
	STACK_END = STACK_TOP - STACK_SIZE;
	STACK_ROM = BSS_ROM + BSS_size;
	.stack_segment STACK_END : AT(STACK_ROM)
	{
		* ( .stack_section* )

	}

	/DISCARD/ : { *(.eh_frame) }

}