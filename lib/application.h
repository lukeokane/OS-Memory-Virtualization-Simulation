#ifndef APPLICATION_H
#define  APPLICATION_H
#include "memory.h"

// data type for defining the application
typedef struct Application {

	// Functions
	void (*start)(struct Application* app);
	void (*clear_screen)();
	
	// Member variables
  Memory memory;
	
} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start(struct Application* app);

// Skip lines on terminal to clear view
void clear_screen();

#endif
