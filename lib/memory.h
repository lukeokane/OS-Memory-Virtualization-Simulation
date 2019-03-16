#ifndef MEMORY_H
#define MEMORY_H

// data type for defining memory
typedef struct {

  unsigned short int* allocated;

} Memory;

// Instance of Memory with memory allocated
Memory new_memory(char addressSize);

#endif
