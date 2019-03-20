#ifndef MEMORY_MANAGEMENT_UNIT_H 
#define MEMORY_MANAGEMENT_UNIT_H 
#include "memory.h"
#include "page_table.h"
#include "address.h"
 
// data type for defining page entry 
typedef struct MemoryManagementUnit { 
 
	// Functions
	FrameEntry (*translate_virtual_address)(struct MemoryManagementUnit *mmu, unsigned int virtual_address);

	// Member variables
  Memory memory;

	PageTable* page_tables;
 
} MemoryManagementUnit;

// Instance with data type functions instantiated
MemoryManagementUnit new_mmu();

// Translate virtual address to a physical address
FrameEntry translate_virtual_address(MemoryManagementUnit *mmu, unsigned int virtual_address);

#endif 

