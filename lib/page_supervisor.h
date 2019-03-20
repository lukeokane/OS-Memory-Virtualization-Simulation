#ifndef PAGE_SUPERVISOR_H
#define PAGE_SUPERVISOR_H
#include "math.h"
#include "memory.h"
#include "page_table.h"

// Page Supervisor - creates & manages page tables
// data type for defining page supervisor 
typedef struct PageSupervisor { 

	// Functions
	void (*populate_random_data)(struct PageSupervisor* page_supervisor);
	PageTable* (*init_process_page_table)(struct PageSupervisor* page_supervisor);
	
	PageTable* page_tables;
	unsigned short page_tables_counter;
	unsigned short page_table_size_bytes;
	unsigned short page_size_bytes;
	Memory memory;

} PageSupervisor;

// Instance with data type functions instantiated
PageSupervisor new_page_supervisor();

// Populate Page Table & write random data to memory
void populate_random_data(struct PageSupervisor* page_supervisor);
 
PageTable* init_process_page_table(struct PageSupervisor* page_supervisor);

#endif 
