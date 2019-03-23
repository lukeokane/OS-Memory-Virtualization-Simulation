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

	printf("Searching translate lookaside buffer for page entry...\n"); 
	// Search in TLB for entry 
	PageEntry* page_entry_tlb = mmu->tlb_search(&mmu->tlb, vpn * mmu->pti.page_size_bytes); 
	
	PageEntry page_entry;

	if (page_entry_tlb != NULL)
	{
		printf("TLB HIT - TLB has an entry for the page number\n");
		page_entry.address = page_entry_tlb->address;
	} else {
	printf("TLB MISS - TLB does not have an entry for the page number");
	printf("Searching page entry in page %d, offset %d.\n", vpn, offset);

	// Get page entry, set "Accessed" bit to 1;
	page_entry = mmu->memory.allocated[vpn * mmu->pti.page_size_bytes].page_entry;
	page_entry.address |= (unsigned short) 1 << 5;
	mmu->memory.allocated[vpn * mmu->pti.page_size_bytes].page_entry = page_entry;
	}
	// Print page entry
	printf("\n");	
	page_entry_header();
	print_page_entry(page_entry);
	printf("\n");

	char present_bit = (page_entry.address >> 0) & 1;

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
		mmu->tlb_add_entry(&mmu->tlb, page_entry, vpn * mmu->pti.page_size_bytes);
		
	} else {
		return -1;
	}
	
	return 0;
}

PageEntry* tlb_search(TLB *tlb, unsigned short virtual_address) {

	for (unsigned char i = 0; i < tlb->total_entries; i++) {
		// Check if page matches and return entry
		if (tlb->entries[i].virt_page == virtual_address)
		{
			// TLB HIT
			return &tlb->entries[i].pe;
		}
	}
	
	// TLB MISS
	return NULL;
}

void tlb_add_entry(struct TLB *tlb, PageEntry pe, unsigned short vpn) {

	TLBEntry tlb_entry;
	tlb_entry.pe = pe;
	tlb_entry.virt_page = vpn;
	// TLB is full, perform FIFO algorithm
	if (tlb->total_entries == tlb->max_entries -1) {
		for (unsigned char i = tlb->max_entries; i > 0; i--) {
			tlb->entries[i] = tlb->entries[i -1];
		}
		tlb->entries[0] = tlb_entry;
	}
 	else {
		tlb->entries[tlb->total_entries] = tlb_entry;
		tlb->total_entries++;
	}
	printf("Page written to TLB.\n");
}

