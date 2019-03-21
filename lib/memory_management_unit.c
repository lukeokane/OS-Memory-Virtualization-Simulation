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
FrameEntry translate_virtual_address(MemoryManagementUnit *mmu, unsigned int virtual_address) {

	printf("\nTranslating virtual address '0x%08x'...\n", virtual_address);
	// Mask to get 8 lowest bits
	unsigned short offset_mask = 0x00FF;

	unsigned short address = virtual_address;

	unsigned short offset = address & offset_mask;

	unsigned short vpn = address >> 8;
	
	unsigned short index = (vpn * mmu->pti.page_table_size_bytes) + offset;

	printf("Searching page entry in page %d, offset is %d.\n", vpn, offset);
	
	// TODO: READ PAGE ENTRIES AFTER DOING POPULATING DATA
	//PageEntry page = (vpn * mmu->pti.page_table_size_bytes) + offset;

	// Get frame
	// Calculate bytes taken by page tables
	unsigned short page_tables_memory = mmu->pti.page_tables_counter * mmu->pti.page_table_size_bytes;
	printf("Page table size bytes: %d\n", page_tables_memory);
	unsigned short frame = (vpn * mmu->pti.page_table_size_bytes) + page_tables_memory;
	unsigned short frame_with_offset = frame + offset;
	printf("Start location of frame is: %d\n", frame);
	printf("offset is: %d\n", frame_with_offset);

	
	//printf("tableentryfromemoryvaluetest12345678: %p\n", &memory->allocated[0].page_entry);
	
	printf("Address 0x%X = VPN: 0x%X, offset: 0x%X\n", address, vpn, offset);
	FrameEntry frame_entry = mmu->memory.allocated[512].frame_entry;
	return frame_entry;
}

