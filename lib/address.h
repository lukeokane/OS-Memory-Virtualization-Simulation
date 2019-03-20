#ifndef ADDRESS_H
#define ADDRESS_H
#include "page_entry.h"
#include "frame_entry.h"

// data type that allows storage of different ...
// ... data types in same memory space
typedef struct Address {
	union {
		struct PageEntry page_entry;
		struct FrameEntry frame_entry;
	};
} Address;

#endif
