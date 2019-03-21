#include <stdio.h>
#include "application.h"

/* 
 * Create Application data type to begin UI interaction...
 * ... with memory virtualization simulation
 * @return Application data type with instantiated functions
 *
 */
Application new_application() {

	Application application = { start, clear_screen };
	return application;
}

/* 
 * Generate UI and create memory virtualization simulation
 * @return void
 *
 */
void start(struct Application* app) {

	// Initialize Page Supervisor and MMU instance
	app->page_supervisor = new_page_supervisor();
	app->cpu.mmu = new_mmu();
	app->clear_screen();

	printf("Application started...\nCreating physical memory...\n");

	// Create physical memory sufficient to store...
  // ... all bytes for system address space
	unsigned char addressSize = 16;
	// MMU & Page Supervisor have reference to physical memory
	app->cpu.mmu.memory = new_memory(addressSize);
	app->page_supervisor.memory = app->cpu.mmu.memory;

	printf("MMU and Page Supervisor now have reference to physical memory.\n");

	// Create page tables and manage via Page Supervisor software, give MMU reference to page tables
	app->cpu.mmu.pti = *app->page_supervisor.init_process_page_table(&app->page_supervisor);

	// Populate page tables & write random data to process.
	app->page_supervisor.populate_random_data(&app->page_supervisor);
}

/* 
 * Skip 10 lines to clear screen space for new action
 * @return void
 *
 */
void clear_screen() {
	printf("\n\n\n\n\n\n\n\n\n\n");
}


