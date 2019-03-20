#include <stdio.h> 
#include "page_table.h"

/* 
 * Create PageTable data type to interact with...
 * ... simulated page tables
 * @return PageTable data type with instantiated functions
 *
 */
PageTable new_page_table() {

	PageTable page_table = {};
	return page_table;
}


void populate(struct PageTable* page_table, struct Memory* memory) {

	printf("Creating Page Table");	

}
