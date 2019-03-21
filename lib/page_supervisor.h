#ifndef PAGE_SUPERVISOR_H
#define PAGE_SUPERVISOR_H
#include <stdlib.h>
#include <stdio.h> 
#include <time.h>
#include "math.h"
#include "memory.h"
#include "page_table.h"
#include "page_tables_info.h"

// Page Supervisor - creates & manages page tables
// data type for defining page supervisor 
typedef struct PageSupervisor { 

	// Functions
	void (*populate_random_data)(struct PageSupervisor* page_supervisor);
	PageTable* (*init_process_page_table)(struct PageSupervisor* page_supervisor);
	
	/* Member variables */

	// Page table information
	PageTable* page_tables;
	PageTablesInfo pti;

	Memory memory;
	/* End member variables */

} PageSupervisor;

// Instance with data type functions instantiated
PageSupervisor new_page_supervisor();

// Populate Page Table & write random data to memory
void populate_random_data(struct PageSupervisor* page_supervisor);
 
PageTable* init_process_page_table(struct PageSupervisor* page_supervisor);

#endif 
