#ifndef MEMORY_MANAGEMENT_UNIT_H 
#define MEMORY_MANAGEMENT_UNIT_H 
#include "memory.h"
#include "page_tables_info.h"
#include "address.h"
#include "print_util.h"
 
// data type for defining page entry 
typedef struct MemoryManagementUnit { 
 
	// Functions
	FrameEntry (*translate_virtual_address)(struct MemoryManagementUnit *mmu, unsigned short virtual_address);

	/* Member variables */
 	Memory memory;
	PageTablesInfo pti;
	/* End member variables */
	
 
} MemoryManagementUnit;

// Instance with data type functions instantiated
MemoryManagementUnit new_mmu();

// Translate virtual address to a physical address
FrameEntry translate_virtual_address(MemoryManagementUnit *mmu, unsigned short virtual_address);

#endif 

