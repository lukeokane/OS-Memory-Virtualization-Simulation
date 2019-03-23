#ifndef MEMORY_MANAGEMENT_UNIT_H 
#define MEMORY_MANAGEMENT_UNIT_H 
#include "memory.h"
#include "page_tables_info.h"
#include "address.h"
#include "print_util.h"
#include "tlb.h"
 
// data type for defining page entry 
typedef struct MemoryManagementUnit { 
 
	// Functions
	signed char (*translate_virtual_address)(struct MemoryManagementUnit *mmu, unsigned short virtual_address);
	PageEntry* (*tlb_search)(struct TLB *tlb, unsigned short page_number);
	void (*tlb_add_entry)(struct TLB *tlb, PageEntry pe, unsigned short vpn);
	/* Member variables */
 	Memory memory;
	PageTablesInfo pti;
	TLB tlb;
	/* End member variables */
	
 
} MemoryManagementUnit;

// Instance with data type functions instantiated
MemoryManagementUnit new_mmu();

// Translate virtual address to a physical address
signed char translate_virtual_address(MemoryManagementUnit *mmu, unsigned short virtual_address);

PageEntry* tlb_search(struct TLB *tlb, unsigned short virtual_address);

void tlb_add_entry(struct TLB *tlb, PageEntry pe, unsigned short vpn);

#endif 
