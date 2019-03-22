#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "external_disk.h"


/* 
 * Allocate Memory data type to simulate physical memory
 * @param addressSize - the size of the memory addresses
 * @return Memory data type with memory allocated
 *
 */
ExternalDisk new_external_disk(unsigned char addressSize)
{
	ExternalDisk ed;
	
	printf("External disk memory being created...\n");
	// Allocate memory for external disk size
  	ed.memory = new_memory(addressSize);
	ed.addresses_filled = 0;

	return ed;
}
