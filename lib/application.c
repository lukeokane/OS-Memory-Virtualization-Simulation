#include <stdio.h>
#include "application.h"

/* 
 * Create Application data type to begin UI interaction...
 * ... with memory virtualization simulation
 * @return Application data type with instantiated functions
 *
 */
Application new_application() {

	Application application = { start, clear_screen };
	return application;
}

/* 
 * Generate UI and create memory virtualization simulation
 * @return void
 *
 */
void start(struct Application* app) {

	app->clear_screen();
	printf("Application started...\nCreating physical memory...\n");
	// Create physical memory sufficient to store...
  // ... all bytes for system address space
	unsigned char addressSize = 16;
	app->memory = new_memory(addressSize);
}

/* 
 * Skip 10 lines to clear screen space for new action
 * @return void
 *
 */
void clear_screen() {
	printf("\n\n\n\n\n\n\n\n\n\n");
}


