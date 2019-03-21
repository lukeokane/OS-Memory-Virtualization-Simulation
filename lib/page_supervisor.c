
#include "page_supervisor.h" 

PageSupervisor new_page_supervisor() {
	PageSupervisor page_supervisor = { populate_random_data, init_process_page_table };
	return page_supervisor;
}

void populate_random_data(struct PageSupervisor* page_supervisor) {

	printf("\nCreating random data...\n");

	unsigned short min_random_bytes = 2048;
	unsigned short max_random_bytes = 20480;

	srand(time(NULL));

	// Generate random no. of bytes between 2048 and 20480
	unsigned short random_bytes = rand() % (max_random_bytes - min_random_bytes) + min_random_bytes;
	// Get number of frame entries possible with the random bytes
	unsigned short frame_entry_amount = random_bytes / page_supervisor->pti.address_space;

	printf("Pseudorandomly generated number of bytes to write: %d, that totals to %d frame entries.\n", random_bytes, frame_entry_amount);
	printf("Beginning writing of pseudorandom data to pseudorandom memory locations...\n");

	unsigned short page_tables_bytes_allocated = page_supervisor->pti.page_table_size_bytes * page_supervisor->pti.page_tables_counter;
	
	for (unsigned short i = 0; i < frame_entry_amount; i++) {
		// Write frame entry to pseudorandom memory address that is not used by page tables. 
		unsigned short random_free_address = rand() % (int) (pow(2, (double) page_supervisor->pti.address_space) - page_tables_bytes_allocated) + page_tables_bytes_allocated;

		// At the minute, this free address could be allocated...
		// ... but the address could create unusable gaps in memory.
		// Using modular arithmethic will ensure that creating a new frame...
		// ... will not cause unusable gaps to occur between frame, since every address will...
		// ... begin on a bit divisible by the address space.
		// e.g. every frame will written to the n*16 bit.
		if (random_free_address % page_supervisor->pti.address_space == 0) {

			// e.g if the address is byte no. 12345 (0x3039)
			// to get frame number, lose first 8 bits by using a mask
			// address: 			0x3039 (12345 bytes)
			// mask:					0xFF00
			// frame number:	0x3000 (12288 bytes)
			unsigned short frame_mask = 0xFF00;
			unsigned short frame_number = random_free_address & frame_mask;

			// Create page entry
			PageEntry page_entry;
			page_entry.address = frame_number;

			// Set entry's 'present' bit to 1/true.
			// This is bit 0 in this page entry architecture
			page_entry.address |= (unsigned short) 1;

			// Set entry's 'read/write' bit to 1/write
			// page_entry.address 		 : 1111 1111 0000 0001
			// (unsigned short) 1 << 1 : 0000 0000 0000 0010
			// 													 -------------------
			// OR											 : 1111 1111 0000 0011
			page_entry.address |= (unsigned short) 1 << 1;

			// Add page entry to memory
			page_supervisor->memory.allocated[i].page_entry = page_entry;

			// Get current page table entry offset to corresponding frame entry offset 
			unsigned short frame_offset = i % page_supervisor->pti.page_table_size_bytes; 
			unsigned short frame_entry_address = frame_number + frame_offset; 
			//printf("frame number address is: %4u, frame number address will be: %4u since offset is %d\n", frame_number, frame_entry_address, i % page_supervisor->pti.page_table_size_bytes); 
 
			// Get random number or alphabetic character and store in frame_entry 
			unsigned char random_ascii = rand() % (0x5A - 0x30) + 0x30; 
			FrameEntry frame_entry; 
			frame_entry.address = random_ascii; 
 
			// Write frame entry to memory 
			page_supervisor->memory.allocated[frame_entry_address].frame_entry = frame_entry;
		}
		// if modulus is not 0, need reduce i to attempt to get a valid address
	  else {
			i--;
		}
	}
	printf("%d data entries successfully written.\n", frame_entry_amount);
}

/*
 * On creating a new process, create enough page tables to...
 * .. address all physical memory
 * @param page_supervisor the Operating System's software...
 * ... to create and manage page tables
 * @return array of data type PageTable filled with a list of...
 * ... page tables in physical memory
 */
PageTablesInfo* init_process_page_table(struct PageSupervisor* page_supervisor) {


	printf("\nCreating page tables...\n");

	// 512 bytes of memory for page table entries (256 PTEs) neccessary to address all physical memory, ...
	// 2 page tables are required due to spec specifying page table sizes of 256 bytes only.

	unsigned short address_space = 16;
	unsigned short page_table_size_bytes = 256;
	unsigned short page_size_bytes = 2;

	// Store information in page supervisor
	page_supervisor->pti.address_space = address_space;
	page_supervisor->pti.page_table_size_bytes = page_table_size_bytes;
	page_supervisor->pti.page_size_bytes = page_size_bytes;

	// Calculate pages required to address all memory
	unsigned short page_size_log2_num = log2(page_table_size_bytes);
	unsigned short pages_required = pow(2, address_space) / pow(2, page_size_log2_num);

	printf("Pages required to address 2^%d address spaces: %d.\n", address_space, pages_required);

	// Calculate memory required to hold all pages
	unsigned short memory_required = pages_required * page_size_bytes;
	// Calculate how many pages per table
	unsigned short page_table_entry_size = page_table_size_bytes / page_size_bytes;
	// Calculate the number of tables required
	unsigned short page_tables_required = memory_required / page_table_size_bytes;

	printf("Page tables can hold %d pages each, number of tables required to contain %d pages: %d.\n", page_table_entry_size, pages_required, page_tables_required);

	printf("Physical memory required to hold all pages: %d bytes.\n", memory_required);

	// Page Supervisor creates space in it's own storage...
	// to store information regarding page tables in physical memory.
	page_supervisor->pti.page_tables = malloc(page_tables_required * sizeof(PageTable));

	unsigned short i;

	for (i = 0; i < page_tables_required; i++) {
		PageTable page_table;
		page_table.start_point = i * page_table_size_bytes;
		page_table.end_point = ((i + 1) * page_table_size_bytes) - 1;

		// Add page to Page Supervisor
		page_supervisor->pti.page_tables[i] = page_table;
		
		printf("Page table #%d created, resides in physical memory 0x%X to 0x%X.\n", i + 1, page_supervisor->pti.page_tables[i].start_point, page_supervisor->pti.page_tables[i].end_point);
	}

	// Save number of page tables in page supervisor
	page_supervisor->pti.page_tables_counter = i;

	return &page_supervisor->pti;
}
