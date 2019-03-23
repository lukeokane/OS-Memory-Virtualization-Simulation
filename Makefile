# Variables
CC      = gcc
CFLAGS  = -c -Wall
LIB_DIR  = lib
DIST_DIR  = dist
OBJECTS = $(DIST_DIR)/main.o\
	  $(DIST_DIR)/application.o\
	  $(DIST_DIR)/memory.o -lm\
	  $(DIST_DIR)/page_entry.o\
	  $(DIST_DIR)/frame_entry.o\
	  $(DIST_DIR)/address.o\
	  $(DIST_DIR)/memory_management_unit.o\
	  $(DIST_DIR)/page_supervisor.o\
	  $(DIST_DIR)/page_table.o\
	  $(DIST_DIR)/page_tables_info.o\
	  $(DIST_DIR)/print_util.o\
	  $(DIST_DIR)/external_disk.o\

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

# Target compiles cpu.c into an object (.o) file
# Depends on cpu.c to be present in order to compile
$(DIST_DIR)/cpu.o: $(LIB_DIR)/cpu.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/cpu.o

# Target compiles memory_management_unit.c into an object (.o) file
# Depends on memory_management_unit.c to be present in order to compile
$(DIST_DIR)/memory_management_unit.o: $(LIB_DIR)/memory_management_unit.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/memory_management_unit.o

# Target compiles page_supervisor.c into an object (.o) file
# Depends on page_supervisor.c to be present in order to compile
$(DIST_DIR)/page_supervisor.o: $(LIB_DIR)/page_supervisor.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/page_supervisor.o

# Target compiles page_table.c into an object (.o) file
# Depends on page_table.c to be present in order to compile
$(DIST_DIR)/page_table.o: $(LIB_DIR)/page_table.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/page_table.o

# Target compiles page_tables_info.c into an object (.o) file
# Depends on page_tables_info.c to be present in order to compile
$(DIST_DIR)/page_tables_info.o: $(LIB_DIR)/page_tables_info.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/page_tables_info.o

# Target compiles print_util.c into an object (.o) file
# Depends on print_util.c to be present in order to compile
$(DIST_DIR)/print_util.o: $(LIB_DIR)/print_util.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/print_util.o

# Target compiles external_disk.c into an object (.o) file
# Depends on external_disk.c to be present in order to compile
$(DIST_DIR)/external_disk.o: $(LIB_DIR)/external_disk.c
	$(CC) $(CFLAGS) $? -o $(DIST_DIR)/external_disk.o

# Remove all built files, and re-create the dist directory
clean:
	rm -rf ./$(DIST_DIR) && mkdir $(DIST_DIR)
