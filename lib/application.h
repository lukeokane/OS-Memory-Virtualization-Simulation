#ifndef APPLICATION_H
#define  APPLICATION_H
#include "cpu.h"
#include "page_supervisor.h"

// data type for defining the application
typedef struct Application {

	// Functions
	void (*start)(struct Application *app);
	void (*clear_screen)();
	void (*write_txt_files)(struct MemoryManagementUnit *mmu);
	
	// Member variables
	CPU cpu;
	PageSupervisor page_supervisor;
	
} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start(struct Application *app);

// Skip lines on terminal to clear view
void clear_screen();

// Write out physical memory and page tables
void write_txt_files(struct MemoryManagementUnit *mmu);

#endif
