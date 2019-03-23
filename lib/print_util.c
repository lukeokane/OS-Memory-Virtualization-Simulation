#include <stdio.h> 
#include "print_util.h"

void page_entry_legend() {
		// Legend
	printf("\n\nPAGE TABLE ENTRY ARCHITECTURE LEGEND\n-----------\nFN   - Frame number\n*NU* - Not Used\nD    - Dirty\nA    - Accessed\nNU - Not Used\n");
	printf("NU - Not Used\nU/S  - User/supervisor\nR/W  - Read/write\nP    - Present\n----------\n\n");
}

void page_entry_header() {

	printf("                    Page Table Entry                 \n");
	printf("    FN    | *NU* | D | A | *NU* | *NU* | U/S | R/W | P |\n");
	printf("------------------------------------------------------\n");
}

void print_page_entry(PageEntry page_entry) {

	unsigned short FN = page_entry.address & (unsigned short) 0xFF00;
	unsigned char NU = 0;
	unsigned char D = (page_entry.address >> 6) & 1;
	unsigned char A = (page_entry.address >> 5) & 1;
	unsigned char PCD = (page_entry.address >> 4) & 1;
	unsigned char PWT = (page_entry.address >> 3) & 1;
	unsigned char UorS = (page_entry.address >> 2) & 1;
	unsigned char RorW = (page_entry.address >> 1) & 1;
	unsigned char P = (page_entry.address >> 0) & 1;

	printf("  0x%04X  |   %d  | %d | %d |   %d  |   %d  |  %d  |  %d  | %d |\n", FN, NU, D, A, PCD, PWT, UorS, RorW, P);
}
