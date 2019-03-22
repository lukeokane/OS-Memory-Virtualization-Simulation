#include <stdio.h>
#include "memory_management_unit.h"

/* 
 * Create MemoryManagementUnit data type
 * @return MemoryManagementUnit data type with instantiated functions
 *
 */
MemoryManagementUnit new_mmu() {

	MemoryManagementUnit mmu = { translate_virtual_address };
	return mmu;
}

/* 
 * Translate virtual memory address to a physical memory address
 * @param *address virtual memory address
 * @return Address the virtual memory address' corresponding physical memory address
 *
 */
FrameEntry translate_virtual_address(MemoryManagementUnit *mmu, unsigned short virtual_address) {

	printf("\nTranslating virtual address '0x%08x'...\n", virtual_address);
	// Mask to get 8 lowest bits
	unsigned short offset_mask = 0x00FF;

	unsigned short address = virtual_address;

	unsigned short offset = virtual_address & offset_mask;

	unsigned short vpn = virtual_address >> 8;
	
	unsigned short index = (vpn * mmu->pti.page_table_size_bytes) + offset;

	printf("Searching page entry in page %d, offset %d.\n", vpn, offset);

	// Get page entry
	PageEntry page_entry = mmu->memory.allocated[vpn].page_entry;

	// Print page entry
	printf("\n");	
	page_entry_header();
	print_page_entry(page_entry);
	printf("\n");
		

	unsigned char present_bit = (page_entry.address >> 0) & 1;

	// TODO: READ PAGE ENTRIES AFTER DOING POPULATING DATA
	// TODO: CHECKING IF PAGE IS VALID BUT NEEDS TO THROW PAGE FAULT
	// ... OR THROW IF THE PAGE ENTRY IS BLANK

	if (present_bit == 1) {

		printf("Valid page entry, frame is present in memory.\n");
	
		unsigned short FN = page_entry.address & (unsigned short) 0xFF00;

		printf("Retreiving frame from frame number %d at offset %d...\n", FN / mmu->pti.page_table_size_bytes, offset);

		// Get frame entry, multiply offset by page size bytes since all frame entries are 2 bytes
		FrameEntry frame_entry = mmu->memory.allocated[FN + offset].frame_entry;

		// Print char if char, otherwise it has no data written to it so just print the value
		if (frame_entry.address != 0) {
			printf("Retrieved frame, data in the frame is: '%c'\n", frame_entry.address);
		} else { 
			printf("Retrieved frame, data in the frame is: '%04d'\n", frame_entry.address);
		}
	}

	
	
	
	// TODO: READ PAGE ENTRIES AFTER DOING POPULATING DATA
	// TODO: CHECKING IF PAGE IS VALID BUT NEEDS TO THROW PAGE FAULT
	// ... OR THROW IF THE PAGE ENTRY IS BLANK
	//PageEntry page = (vpn * mmu->pti.page_table_size_bytes) + offset;

	// Get frame
	// Calculate bytes taken by page tables
	//unsigned short page_tables_memory = mmu->pti.page_tables_counter * mmu->pti.page_table_size_bytes;
	//printf("Page table size bytes: %d\n", page_tables_memory);
	//unsigned short frame = (vpn * mmu->pti.page_table_size_bytes) + page_tables_memory;
	//unsigned short frame_with_offset = frame + offset;
	//printf("Start location of frame is: %d\n", frame);
	//printf("frame with offset is: %d\n", frame_with_offset);

	
	//printf("tableentryfromemoryvaluetest12345678: %p\n", &memory->allocated[0].page_entry);
	
	//printf("Address 0x%X = VPN: 0x%X, offset: 0x%X\n", address, vpn, offset);
	FrameEntry frame_entry = mmu->memory.allocated[512].frame_entry;
	return frame_entry;
}

