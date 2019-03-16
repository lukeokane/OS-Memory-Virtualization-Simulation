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
Memory new_memory(char addressSize)
{
  Memory memory;
	
	// addressSize can address 2^addressSize bytes of memory
	// so allocate 2^addressSize
  memory.allocated = malloc(pow(2, (double) addressSize));

  return memory;
}
