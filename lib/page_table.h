#ifndef PAGE_TABLE_H 
#define PAGE_TABLE_H
#include "memory.h"

// data type for defining page table
typedef struct PageTable { 

	// Member variables
	unsigned short start_point;
	unsigned short end_point;

} PageTable;

// Instance with data type functions instantiated
PageTable new_page_table();
 
#endif
