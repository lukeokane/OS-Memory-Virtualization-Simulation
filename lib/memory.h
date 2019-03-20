#ifndef MEMORY_H
#define MEMORY_H
#include "address.h"

// data type for defining memory
typedef struct Memory {

  Address* allocated;

} Memory;

// Instance of Memory with memory allocated
Memory new_memory(unsigned char addressSize);

// Tested method to check Address union struct...
// ... is infact taking only 2 bytes in Memory
// REMOVE LATER
void createPageTablesTest(struct Memory *memory);
// REMOVE LATER

#endif
