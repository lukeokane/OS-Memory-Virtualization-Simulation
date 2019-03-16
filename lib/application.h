#ifndef APPLICATION_H
#define  APPLICATION_H
#include "memory.h"

// data type for defining the application
typedef struct Application {

	void (*start)();
  Memory memory;

} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start(struct Application* app);

void clearScreen();

#endif
