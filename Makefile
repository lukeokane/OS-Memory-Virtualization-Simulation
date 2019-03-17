# Variables
CC      = gcc
CFLAGS  = -c -Wall
LIB_DIR  = lib
DIST_DIR  = dist
OBJECTS = $(DIST_DIR)/main.o\
	  $(DIST_DIR)/application.o\
	  $(DIST_DIR)/memory.o -lm\
	  $(DIST_DIR)/page_entry.o\
	  $(DIST_DIR)/frame_entry.o

# "-lm" links math.h implementaton to memory.o

# Syntax:
# target: dependencies
# command

# A full, incremental build (also, as first rule, the default)
default: link

# Final compile line after all dependencies (list of .o files in OBJECTS) are fulfilled.
link: $(OBJECTS)
	$(CC) $? -o $(DIST_DIR)/simulate

# Target compiles main.c into an object (.o) file
# Depends on main.c to be present in order to compile
$(DIST_DIR)/main.o: $(LIB_DIR)/main.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/main.o

# Target compiles application.c into an object (.o) file
# Depends on application.c to be present in order to compile
$(DIST_DIR)/application.o: $(LIB_DIR)/application.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/application.o

# Target compiles memory.c into an object (.o) file
# Depends on memory.c to be present in order to compile
$(DIST_DIR)/memory.o: $(LIB_DIR)/memory.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/memory.o

# Target compiles page_entry.c into an object (.o) file
# Depends on page_entry.c to be present in order to compile
$(DIST_DIR)/page_entry.o: $(LIB_DIR)/page_entry.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/page_entry.o

# Target compiles frame_entry.c into an object (.o) file
# Depends on frame_entry.c to be present in order to compile
$(DIST_DIR)/frame_entry.o: $(LIB_DIR)/frame_entry.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/frame_entry.o

# Target compiles address.c into an object (.o) file
# Depends on address.c to be present in order to compile
$(DIST_DIR)/address.o: $(LIB_DIR)/address.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/address.o

# Remove all built files, and re-create the dist directory
clean:
	rm -rf ./$(DIST_DIR) && mkdir $(DIST_DIR)
