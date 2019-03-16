# Variables
CC      = gcc
CFLAGS  = -c -Wall
LIB_DIR  = lib
DIST_DIR  = dist
OBJECTS = $(DIST_DIR)/main.o\
	  $(DIST_DIR)/application.o

# Syntax:
# target: dependencies
# 	command

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

# Remove all built files, and re-create the dist directory
clean:
	rm -rf ./$(DIST_DIR) && mkdir $(DIST_DIR)
