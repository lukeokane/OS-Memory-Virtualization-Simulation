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
															write_external_disk, write_tlb,
															user_prompt };
	return application;
}

/* 
 * Generate UI and create memory virtualization simulation
 * @return void
 *
 */
void start(struct Application* app) {

	app->clear_screen();
	printf("Application started...\n");

	// Initialize External Disk, Page Supervisor and MMU instance
	// Cannot use malloc() in a function to create an instance of a data type, ...
	// causes MAJOR	problem with different variables pointing to same address
	unsigned char address_size = 16;
	app->page_supervisor = new_page_supervisor();
	app->memory.allocated = malloc(pow(2, (double) address_size));
	app->cpu.mmu = new_mmu();
	unsigned char external_address_size = 16;
	app->ssd.size = pow(2, external_address_size);
	app->ssd.memory.allocated = malloc(pow(2, external_address_size));
	app->tlb.entries = malloc(16 * sizeof(TLBEntry));

	// Give reference to external disk to page supervisor
	app->page_supervisor.ssd = app->ssd;

	printf("Creating physical memory...\n");

	// Create physical memory sufficient to store...
	// ... all bytes for system address space
	// MMU & Page Supervisor have reference to physical memory
	app->cpu.mmu.memory = app->memory;
	app->page_supervisor.memory = app->memory;

	printf("MMU and Page Supervisor now have reference to physical memory.\n");
	printf("Page Supervisor now has reference to external disk.\n");

	// Create page tables and manage via Page Supervisor software, give MMU reference to page tables
	app->cpu.mmu.pti = *app->page_supervisor.init_process_page_table(&app->page_supervisor);

	// Populate page tables & write random data to memory.
	app->page_supervisor.populate_random_data(&app->page_supervisor);

	// Print human readable description of page table entry structure
	page_entry_legend();
	page_entry_header();
	PageEntry pe;
	pe.address = 0x3F23;
	print_page_entry(pe);

	// Write populated data to .txt files
	app->write_txt_files(app);

	// Display prompt to enter virtual address until exit (CTRL+C)
	do {
	unsigned short virtual_address = app->user_prompt();
	signed char result = app->cpu.mmu.translate_virtual_address(&app->cpu.mmu, virtual_address);

	if (result == -1){
		printf("--PAGE FAULT THROWN BY CPU--\n");
		printf("--EXCEPTION CAUGHT BY OS EXCEPTION HANDLING SOFTWARE (Page Supervisor)---\n");
	 	signed char result = app->page_supervisor.page_to_memory(&app->page_supervisor, virtual_address);
		// PT entry now in memory if return result is 0, so retry translation
		if (result == 0) {
		printf("\n\nPage Supervisor returns a value to the CPU to restart translation\n");
		app->cpu.mmu.translate_virtual_address(&app->cpu.mmu, virtual_address);
		}
	}
	app->write_txt_files(app);
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
 * contents to 3 txt files
 * @return void
 *
 */
void write_txt_files(struct Application *app) {
  app->write_physical_memory(&app->cpu.mmu);
	app->write_page_table(&app->cpu.mmu);
	app->write_external_disk(&app->page_supervisor);
	app->write_tlb(&app->tlb);
}

/* 
 * Write out physical memory contents
 * @return void
 *
 */
void write_physical_memory(struct MemoryManagementUnit *mmu) {
	
	FILE *pmf = fopen("./data/physical_memory.txt", "w+");

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
	fprintf(ptf, "PAGE TABLE ENTRY ARCHITECTURE LEGEND\n-----------\nFN   - Frame number\n*NU* - Not Used\nD    - Dirty\nA    - Accessed\n*NU* - Not Used\n");
	fprintf(ptf, "*NU* - Not Used \nU/S  - User/supervisor\nR/W  - Read/write\nP    - Present\n----------\n\n");
	// Table layout
	fprintf(ptf, "  Page  |                    Page Table Entry                   |\n");
	fprintf(ptf, "        |    FN    | *NU* | D | A | *NU* | *NU* | U/S | R/W | P |\n");
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
	
	fprintf(ptf, "0x%04X  |  0x%04X  |   %d  | %d | %d |   %d  |   %d  |  %d  |  %d  | %d |\n", i, FN, NU, D, A, PCD, PWT, UorS, RorW, P);

	}

	// Close stream
	fclose(ptf);

}

void write_external_disk(struct PageSupervisor *page_supervisor) {
	FILE *edf = fopen("./data/external_disk.txt", "w+");
	
	fprintf(edf, "NOTE: While the addresses returned from swapping are correct, there is an issue with memory from another variable overlapping the external disk array.\n");
	fprintf(edf, "So junk data will appear in areas, but the 2 pages swapped out at the beginning are correct. Did not have time to fix the issue.\n\n");

	fprintf(edf, "  Ext. Disk Addr.  | Content  |\n"); 
	fprintf(edf, "------------------------------|\n");

	for (unsigned int i = 0; i < page_supervisor->ssd.size; i++) {
		FrameEntry fe = page_supervisor->ssd.memory.allocated[i].frame_entry;

		char null_text[] = "null";
		if (fe.address != 0x0) {
			fprintf(edf, "       0x%04X      |%4c (%d) |\n", i, fe.address, fe.address);
		}
		else {
			fprintf(edf, "       0x%04X      | %s (%d) |\n", i, null_text, fe.address);
		}
	}
	fclose(edf);
}

void write_tlb(struct TLB *tlb) {
}

unsigned short user_prompt() {
	printf("\n\n---------------------------------- USER INPUT ---------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("NOTE: 2 page entries (page 2 and 13) are stored externally, their virtual memory addresses are:\n");
	printf("Page 2: 0x0200 to 0x02FF\n");
	printf("Page 13: 0x0D00 to 0x0DFF\n\n");
	printf("On every translation, all .txt files are updated with their up to data values.\n\n");
	printf("\n\nPress CTRL+C to quit.\n"); 
	printf("Enter a virtual address in hexadecimal format (e.g. A3AF2): ");

	unsigned short virtual_address;
	scanf("%hX", &virtual_address);
	printf("-----------------------------------------------------------------\n\n");
  
	return virtual_address;
}
