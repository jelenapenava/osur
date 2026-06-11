/*! linker script for memory layout */

/* Its parsed as C before used in linking! */

ENTRY(arch_startup)

SECTIONS {
	.boot LOAD_ADDR : AT(LOAD_ADDR)
	{
		kernel_code_addr = .;

		/* instructions */
		*?/boot/startup.asm.o ( .text* )

		*( .text* )
	}
	CODE_size = SIZEOF(.code);
	

	.rodata : {

	}
	.data ADDR_DATA : AT(DATA_ROM)
	{
		kernel_data_addr = .;

		/* read only data (constants), initialized global variables */
		* ( .data* )
	}
	DATA_ROM =  CODE_size + LOAD_ADDR;
	DATA_RAM = ADDR_DATA;
	DATA_size = SIZEOF(.data);
	BSS_ROM =  DATA_size + DATA_ROM;
	BSS_RAM = DATA_size + ADDR_DATA;
	.bss BSS_RAM : AT(BSS_ROM)
	{
		*( .bss* COMMON* )

		. = ALIGN (4096);
	}
	BSS_size = SIZEOF(.bss);
	p1_ROM = BSS_ROM + BSS_size;

	.p1 P1ADDR : AT(p1_ROM)
	{
    	p1 = .;
    	. += P1SIZE;
	}

	p2_ROM = p1_ROM + SIZEOF(.p1);
	.p2 P2ADDR : AT(p2_ROM)
	{
    	p2 = .;
    	. += P2SIZE;
	}

	

	/*
	 * what with other sections generated with gcc (various versions)?
	 * if optimizing for size discard them with: /DISCARD/ : { *(*) }
	 * if debugging with qemu/gdb they must be included
	 * - they can be included implicitly, without declaring them here
	 * - but they will be put behind "kernel_end_addr" so its best to use
	 *   multiboot loader (QEMU is that)
	 */
	STACK_END = STACK_TOP - STACK_SIZE;
	STACK_ROM = p2_ROM + SIZEOF(.p2);
	.stack_segment STACK_END : AT(STACK_ROM)
	{
		* ( .stack_section* )

	}

	/DISCARD/ : { *(.eh_frame) }
#ifndef DEBUG
	/DISCARD/ : { *(*) }

#endif
	kernel_end_addr = .;
}