/* Ryan Smith */

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"
#include <stdlib.h>

/* This program allows a user to investigate the contents of a binary file */
/* Takes in a compiled .obj file created for execution on PennSim LC-4 */
/* It creates a linked list of it's contents in order of address and prints all info */
/* Deletes all content held in linked list after printing */

int main () {

	/* creates head pointer to linked list: memory */
	struct row_of_memory* memory = NULL;
	
	/* calls get_file for user input and attempts to open the file, checks for errors. */
	FILE *src_file = get_file();
	if (src_file == NULL){
		fprintf(stderr, "There was an error opening the file.") ;
		return 1;
	}
	
	/* calls parse_file which breaks the file into row_of_memory objects, checks for errors */
	if (parse_file(src_file, &memory) != 0){
		fprintf(stderr, "There was an error while parsing file.");
		return 1;
	}

	/* calls reverse_assemble to look for arithmetic instructions and checks for errors */
	int reverseReturnValue = reverse_assemble(memory);
	if (reverseReturnValue != 0){
		printf("There was an error reverse assembling the list." );
		return 1;
	}

	/* prints the formatted list */
	print_list(memory);

	/* calls delete list and checks for errors */
	memory = delete_list(memory);
	if(memory != NULL){
		printf("There was an error deleting the list.");
		return 1;
	}

	/* returns 0 if everything executed properly */
	return 0 ;
}
