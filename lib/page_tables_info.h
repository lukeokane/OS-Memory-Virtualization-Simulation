#ifndef PAGE_TABLES_INFO_H 
#define PAGE_TABLES_INFO_H

// data type for defining page table
typedef struct PageTablesInfo { 

	// Member variables
	unsigned short page_tables_counter;
	unsigned short page_table_size_bytes;
	unsigned short page_size_bytes;
	unsigned char address_space;

} PageTablesInfo;

#endif
