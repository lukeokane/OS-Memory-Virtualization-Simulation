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

	// Mask to get 8 lowest bits
	unsigned short offset_mask = 0x00FF;

	// Mask to get 8 lowest bits
	unsigned short address = virtual_address;

	unsigned short offset = address & offset_mask;

	unsigned short vpn = address >> 8;
	//printf("tableentryfromemoryvaluetest12345678: %p\n", &memory->allocated[0].page_entry);
	
	printf("Address 0x%X = VPN: 0x%X, offset: 0x%X\n", address, vpn, offset);
	FrameEntry frame_entry = mmu->memory.allocated[512].frame_entry;
	return frame_entry;
}

