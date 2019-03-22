#include <stdio.h>
#include "application.h"

/* 
 * Create Application data type to begin UI interaction...
 * ... with memory virtualization simulation
 * @return Application data type with instantiated functions
 *
 */
Application new_application() {

	Application application = { start, clear_screen, write_txt_files,
															write_physical_memory, write_page_table,
															user_prompt };
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

	// Write populated data to .txt files
	app->write_txt_files(app);

	//app->cpu.mmu.translate_virtual_address(&app->cpu.mmu, 0x0100);

	// Display prompt to enter virtual address until exit (CTRL+C)
	do {
	unsigned short virtual_address = app->user_prompt();
	app->cpu.mmu.translate_virtual_address(&app->cpu.mmu, virtual_address);
	} while (1 == 1);
}

/* 
 * Skip 10 lines to clear screen space for new action
 * @return void
 *
 */
void clear_screen() {
	printf("\n\n\n\n\n\n\n\n\n\n");
}

/* 
 * Write out physical memory contents and physical memory's page table's...
 * contents to 2 txt files
 * @return void
 *
 */
void write_txt_files(struct Application *app) {
  app->write_physical_memory(&app->cpu.mmu);
	app->write_page_table(&app->cpu.mmu);
}

/* 
 * Write out physical memory contents
 * @return void
 *
 */
void write_physical_memory(struct MemoryManagementUnit *mmu) {
	
	FILE *pmf = fopen("./data/physical_memory.txt", "w+");
	
	fprintf(pmf, "NOTE: While the addresses printed are correct, there is an issue with memory from another variable overlapping the physical memory array.\n");
	fprintf(pmf, "So junk data will appear in areas, did not have time to fix the issue.\n");

	fprintf(pmf, "  Address   | Frame Number | Offset |   Content   |\n"); 
	fprintf(pmf, "--------------------------------------------------|\n");
	
	unsigned short page_tables_size_bytes = mmu->pti.page_table_size_bytes * mmu->pti.page_tables_counter;
	int bytes = pow(2, mmu->pti.address_space);
	for (unsigned int i = page_tables_size_bytes; i < bytes; i++) {
		FrameEntry fe = mmu->memory.allocated[i].frame_entry;
	
		unsigned short FN = i & (unsigned short) 0xFF00;
		unsigned short offset = i & (unsigned short) 0x00FF;
		char null_text[] = "null";
		if (fe.address != 0x0) {
			fprintf(pmf, "   0x%04X   |     %4d     |  %3d   | %4c  (%d)  |\n", i, FN, offset, fe.address, fe.address);
		}
		else {
			fprintf(pmf, "   0x%04X   |     %4d     |  %3d   |   %s (%d)  |\n", i, FN, offset, null_text, fe.address);
		}
	}
	fclose(pmf);
}

/* 
 * Write out physical memory's page table's
 * @return void
 *
 */
void write_page_table(struct MemoryManagementUnit *mmu) {

	FILE *ptf = fopen("./data/page_table.txt", "w+");
	// Legend
	fprintf(ptf, "PAGE TABLE ENTRY ARCHITECTURE LEGEND\n-----------\nFN   - Frame number\n*NU* - Not Used\nD    - Dirty\nA    - Accessed\nPCD  - Page-level cache disable\n");
	fprintf(ptf, "PWT  - Page-level write-through\nU/S  - User/supervisor\nR/W  - Read/write\nP    - Present\n----------\n\n");
	// Table layout
	fprintf(ptf, "  Page  |                    Page Table Entry                 |\n");
	fprintf(ptf, "        |    FN    | *NU* | D | A | PCD | PWT | U/S | R/W | P |\n");
	fprintf(ptf, "---------------------------------------------------------------\n");

	unsigned short entries_per_table = mmu->pti.page_table_size_bytes / mmu->pti.page_size_bytes;
	unsigned short total_page_entries = mmu->pti.page_tables_counter * entries_per_table;

	unsigned short i;
	for (i = 0; i < total_page_entries; i += 2) {
	// Extract all data from page entry
	PageEntry page_entry = mmu->memory.allocated[i].page_entry;

	unsigned short FN = page_entry.address & (unsigned short) 0xFF00;
	unsigned char NU = 0;

	// Get specific bit from data type: (num >> bit) & 1
	// -------------------------------------------------
	// page_entry.address 		 	: 1111 1111 0000 0001
	// (page_entry.address >> 6): 0000 0011 1111 1101
	// 1 (mask)								 	: 0000 0000 0000 0001
	// 													 -------------------
	// AND										 	: 0000 0000 0000 0001
	unsigned char D = (page_entry.address >> 6) & 1;
	unsigned char A = (page_entry.address >> 5) & 1;
	unsigned char PCD = (page_entry.address >> 4) & 1;
	unsigned char PWT = (page_entry.address >> 3) & 1;
	unsigned char UorS = (page_entry.address >> 2) & 1;
	unsigned char RorW = (page_entry.address >> 1) & 1;
	unsigned char P = (page_entry.address >> 0) & 1;
	
	fprintf(ptf, "0x%04X  |  0x%04X  |   %d  | %d | %d |  %d  |  %d  |  %d  |  %d  | %d |\n", i, FN, NU, D, A, PCD, PWT, UorS, RorW, P);

	}

	// Close stream
	fclose(ptf);

}

unsigned short user_prompt() {
	printf("\n\nPress CTRL+C to quit.\n");
	printf("Enter a virtual address in hexadecimal format (e.g. A3AF2): ");

	unsigned short virtual_address;
	scanf("%hX", &virtual_address);
  
	return virtual_address;
}
