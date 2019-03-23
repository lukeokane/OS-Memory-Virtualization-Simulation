#ifndef TLB_ENTRY_H 
#define TLB_ENTRY_H
#include "page_entry.h"

// data type for defining page table
typedef struct TLBEntry { 

	// Member variables
	PageEntry pe;
	unsigned char virt_page;

} TLBEntry;

#endif
