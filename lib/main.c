#include "./application.h"
#include "./memory.h"
#include "./page_entry.h"
 
int main() {
 
	Application app = new_application();
	// Start application
	app.start(&app);

	return 0;
}
