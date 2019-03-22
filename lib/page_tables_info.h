#ifndef PAGE_TABLES_INFO_H 
#define PAGE_TABLES_INFO_H
#include "page_table.h"

// data type for defining page table
typedef struct PageTablesInfo { 

	// Member variables
	unsigned short page_tables_counter;
	unsigned short page_table_size_bytes;
	unsigned short page_size_bytes;
	unsigned char address_space;

	PageTable* page_tables;

} PageTablesInfo;

#endif
