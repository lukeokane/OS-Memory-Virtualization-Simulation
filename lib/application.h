#ifndef APPLICATION_H
#define  APPLICATION_H
#include "cpu.h"
#include "page_supervisor.h"

// data type for defining the application
typedef struct Application {

	// Functions
	void (*start)(struct Application *app);
	void (*clear_screen)();
	
	// Member variables
	CPU cpu;
	PageSupervisor page_supervisor;
	
} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start(struct Application *app);

// Skip lines on terminal to clear view
void clear_screen();

#endif
