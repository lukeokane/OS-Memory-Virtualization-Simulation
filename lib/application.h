#ifndef APPLICATION_H
#define  APPLICATION_H
#include "cpu.h"
#include "memory.h"
#include "page_supervisor.h"
#include "external_disk.h"
#include "print_util.h"

// data type for defining the application
typedef struct Application {

	// Functions
	void (*start)(struct Application *app);
	void (*clear_screen)();
	void (*write_txt_files)(struct Application *app);
	void (*write_physical_memory)(struct MemoryManagementUnit *mmu);
	void (*write_page_table)(struct MemoryManagementUnit *mmu);
	void (*write_external_disk)(struct PageSupervisor *page_supervisor);
	unsigned short (*user_prompt)();
	
	// Member variables
	CPU cpu;
	Memory memory;
	PageSupervisor page_supervisor;
	ExternalDisk ssd;
	
} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start(struct Application *app);

// Skip lines on terminal to clear view
void clear_screen();

// Write out physical memory and page tables in physical memory
void write_txt_files(struct Application *app);

// Write out physical memory
void write_physical_memory(struct MemoryManagementUnit *mmu);

// Write out page tables in physical memory
void write_page_table(struct MemoryManagementUnit *mmu);

// Write out frames in external disk
void write_external_disk(struct PageSupervisor *page_supervisor);

unsigned short user_prompt();

#endif
