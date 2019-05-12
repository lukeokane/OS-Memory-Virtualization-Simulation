# Memory Virtualization Simulation

This application simulates memory virtualizaton for a 16 bit virtual address space with a page size of 256 bytes. The system uses a single-level linear page stored in one block of the system's simulated physical memory. The application received 95.5% score as a part of an Operating Systems module.

## Description of implementation
* One block of memory for page tables and frames
* 2 page tables (256 bytes / 128 entries each as per spec) - 2 bytes per entry.
* Frames of 256 bytes - 1 byte per entry
* Structs with pointers to functions used to modularize entities:
```
unsigned short virtual_address = 0xFF03;
signed char result = app->cpu.mmu.translate_virtual_address(&app->cpu.mmu, virtual_address);
```
* Interact with simulated physical memory array via structs
```
----- address.h -----
typedef struct Address {
  union {
    struct PageEntry page_entry;
    struct FrameEntry frame_entry;
  }
} Address;

----- memory.h -----
typedef struct Memory {
  Address* allocated;
} Memory;

----- memory_management_unit.c -----
SAMPLE 1
PageEntry page_entry = mmu->memory.allocated[vpn * page_size_bytes].page_entry;
.....
mmu->memory.allocated[vpn * page_size_bytes].page_entry = page_entry;

SAMPLE 2
FrameEntry frame_entry = mmu->memory.allocated[frame_no + page_offset].frame_entry;
.....
mmu->memory.allocated[frame_no + page_offset].frame_entry = frame_entry;
```
* Referencing, e.g MMU and Page Supervisor (page fault handling S/W) have references to the simulated physical memory block of memory.
* Translation lookaside buffer using FIFO replacement algorithm
* Memory Management Unit - Virtual address translation
  * Bitwise operations (e.g. shifting, AND for masking, setting page entry bits to 0 or 1)
* External disk with two pages written to it (note: issue with random data in external disk array in some places, however paged data is still accurate.)
* Page Supervisor / Page Fault Handler (OS Software)
  * Handles paging on page fault exception, tells MMU to begin translation after successful paging.
  * Creates and manages page tables.
* Random bytes of data between 2048 and 20480 bytes, location of data on physical memory is also random.
* 4 .txt files containing physical memory data (frames), external disk, TLB entries & page tables respectively.
  * Updated on every address translation.
  
## Page Entry Architecture
The page entry structure was guided by Intel's implementation of page table entries. This format is used by process register CR3. CR3 is a process register (quickly accessible location to the CPU to get) used when virtual addressing is enabled (this is indicated by CR0's bit 31, the PG (Paging) flag).
  
The structure implemented is as follows:
  
![Page entry architecture](https://i.imgur.com/94P3dI5.jpg)
### Breakdown (by bit)
* **0** - Present - if the page is present in physical memory. 1 if present, 0 if in secondary storage.
* **1** - Read/Write permissions - if 0, the translated frame of this entry can be written to. If 1 then the frame is read-only.
* **2** - User/Supervisor - if 0, supervisor-mode users can only access the translated frame. If 1 then a user-mode user can also access
* **3** - NU - Not used.
* **4** - NU - Not used.
* **5** - Accessed - set to 1 when a processor has accessed this page entry, otherwise 0. Only software can change these values after being initially set.
* **6** - Dirty - When a write occurs, set the bit as 1. Only software can change the values after being initially set.
* **7** - NU - Not used.
* **8 - 15** - Physical address of the frame
