#include <stdio.h>
#include "application.h"
#include "memory.h"

/* 
 * Create Application data type to begin UI interaction...
 * ... with memory virtualization simulation
 * @return Application data type with instantiated functions
 *
 */
Application new_application() {

	Application application = { start };
	return application;
}

/* 
 * Generate UI and create memory virtualization simulation
 * @return void
 *
 */
void start() {

	// Create physical memory sufficient to store...
  // ... all bytes for system address space
	Memory memory = new_memory(16);
}


