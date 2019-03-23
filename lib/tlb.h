#ifndef TLB_H 
#define TLB_H
#include "tlb_entry.h"

// data type for defining page table
typedef struct TLB { 

	// Member variables
	TLBEntry* entries;

} TLB;

#endif
