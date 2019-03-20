#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "memory.h"


/* 
 * Allocate Memory data type to simulate physical memory
 * @param addressSize - the size of the memory addresses
 * @return Memory data type with memory allocated
 *
 */
Memory new_memory(unsigned char addressSize)
{
  Memory memory;
	
	// addressSize can address 2^addressSize bytes of memory
	// so allocate 2^addressSize
	double bytes = pow(2, (double) addressSize);
	printf("Physical memory allocated with 2^%0d (%.0lf) bytes.\n", addressSize, bytes);
  memory.allocated = malloc(pow(2, (double) addressSize));
  return memory;
}

/* Tested method to check Address union struct 
	is infact taking only 2 bytes in Memory */
void createPageTablesTest(struct Memory *memory) {
	PageEntry page_entry;
	page_entry.address = 0xDEFF;
	
	FrameEntry frame_entry;
	frame_entry.address = 0x0200;
	
	memory->allocated[0].page_entry = page_entry;
	memory->allocated[512].frame_entry = frame_entry;
	printf("address: %lu\n", sizeof(Address));
	printf("pageentry: %lu\n", sizeof(PageEntry));
	printf("frameentry: %lu\n", sizeof(FrameEntry));
	printf("pageentryfrommemory: %lu\n", sizeof(memory->allocated[0]));
	printf("frameentryfromemory: %lu\n", sizeof(memory->allocated[512]));
	printf("pageentryfromemoryvalue: %d\n", memory->allocated[0].page_entry.address);
	printf("frameentryfromemoryvalue: %d\n", memory->allocated[512].frame_entry.address);
}
