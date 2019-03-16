#ifndef APPLICATION_H
#define  APPLICATION_H

// data type for defining the application
typedef struct {

	void (*start)();

} Application;

// Instance with data type functions instantiated
Application new_application();

// Start application function
void start();

#endif
