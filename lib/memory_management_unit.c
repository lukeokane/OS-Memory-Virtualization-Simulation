#include <stdio.h>
#include "memory_management_unit.h"

/* 
 * Create MemoryManagementUnit data type
 * @return MemoryManagementUnit data type with instantiated functions
 *
 */
MemoryManagementUnit new_mmu() {

	MemoryManagementUnit mmu = { translate_virtual_address, tlb_search, tlb_add_entry };
	return mmu;
}

/* 
 * Translate virtual memory address to a physical memory address
 * @param *address virtual memory address
 * @return Address the virtual memory address' corresponding physical memory address
 *
 */
signed char translate_virtual_address(MemoryManagementUnit *mmu, unsigned short virtual_address) {

	printf("\nTranslating virtual address '0x%04x'...\n", virtual_address);
	// Mask to get 8 lowest bits
	unsigned short offset_mask = 0x00FF;

	unsigned short offset = virtual_address & offset_mask;

	unsigned short vpn = virtual_address >> 8;

	//printf("Address 0x%X = VPN: 0x%X maps to address 0x%X, offset: 0x%X\n", virtual_address, vpn, vpn * mmu->pti.page_size_bytes, offset);

	// Search in TLB for entry
	PageEntry* page_entry_tlb = mmu->tlb_search(&mmu->tlb, virtual_address);
	
	PageEntry page_entry;

	if (page_entry_tlb != NULL)
	{
		page_entry.address = page_entry_tlb->address;
	}
	printf("Searching page entry in page %d, offset %d.\n", vpn, offset);

	// Get page entry, set "Accessed" bit to 1;
	page_entry = mmu->memory.allocated[vpn * mmu->pti.page_size_bytes].page_entry;
	page_entry.address |= (unsigned short) 1 << 5;
	mmu->memory.allocated[vpn * mmu->pti.page_size_bytes].page_entry = page_entry;

	// Print page entry
	printf("\n");	
	page_entry_header();
	print_page_entry(page_entry);
	printf("\n");

	char present_bit = (page_entry.address >> 0) & 1;

	// TODO: READ PAGE ENTRIES AFTER DOING POPULATING DATA
	// TODO: CHECKING IF PAGE IS VALID BUT NEEDS TO THROW PAGE FAULT
	// ... OR THROW IF THE PAGE ENTRY IS BLANK

	if (present_bit == 1) {

		printf("Valid page entry, frame is present in memory.\n");
	
		unsigned short FN = page_entry.address & (unsigned short) 0xFF00;

		printf("Retreiving frame from frame number %d at offset %d (Physical address location 0x%04X)...\n", FN / mmu->pti.page_table_size_bytes, offset, FN + offset);

		// Get frame entry, multiply offset by page size bytes since all frame entries are 2 bytes
		FrameEntry frame_entry = mmu->memory.allocated[FN + offset].frame_entry;

		// Print char if char, otherwise it has no data written to it so just print the value
		if (frame_entry.address > 0) {
			printf("Retrieved frame, data in the frame is: '%c'\n", frame_entry.address);
		} else { 
			printf("Retrieved frame, data in the frame is: '%04d'\n", frame_entry.address);
		}

		// Add to TLB cache
		//mmu->tlb_add_entry(&mmu->tlb, page_entry);
		
	} else {
		return -1;
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
	return 0;
}

PageEntry* tlb_search(TLB *tlb, unsigned short virtual_address) {
	printf("Beginning translate lookaside buffer search...\n");
	
	for (unsigned char i = 0; i < tlb->total_entries; i++) {
		// Check if page matches and return entry
		unsigned char page = (virtual_address & (unsigned short) 0xFF00) >> 8;
		if (tlb->entries[i].virt_page == page)
		{
			printf("TLB HIT - TLB has an entry for the page number\n");
			return &tlb->entries[i].pe;
		}
	}
	
	// TLB MISS
	printf("TLB MISS - No TLB entries matching the page number.\n");
	return NULL;
}

void tlb_add_entry(struct TLB *tlb, PageEntry pe) {
	printf("GOING IN");
}

