#ifndef EXTERNAL_DISK_H
#define EXTERNAL_DISK_H
#include "memory.h"

// data type for defining memory
typedef struct ExternalDisk {

	Memory memory;

	// Entries are filled linear.
	// if had more time, would track page frames
	unsigned short addresses_filled;
	unsigned short size;

} ExternalDisk;

#endif
