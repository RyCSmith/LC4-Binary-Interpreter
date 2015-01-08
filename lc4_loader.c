/* Ryan Smith */
#include <stdio.h>
#include "lc4_memory.h"
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 100

/* provides functions nessary to load an .obj file and parse the contained information */

/* asks user for input, opens file and returns it */
FILE* get_file() 
{
	FILE *src_file;
	char userInput [MAX_LEN];
	fprintf(stdout, "Please enter the name of the file you would like to search: ");
	scanf("%s", userInput);
	src_file = fopen (userInput, "r") ;
	return src_file;
}

/* combine takes two char and concatenates them using shifting, returns single char */
unsigned char combine(unsigned char c, unsigned char c2){
	
	return (c << 8) + c2 ; 

}

/* parses information in .obj and uses it to create nodes of instructions */
int parse_file (FILE* src_file, struct row_of_memory** memory) 
{
	unsigned char label[2];
	short unsigned int address;
	unsigned char n[2];
    /* creates head variable to manipulate "memory" without persistent dereferencing */
    /* alternatively, head could be replaced with "*memory" */
    struct row_of_memory* head = *memory;
    /* loops througth file until reading the end, reads 2 bytes in, advances appropriately based on content */
	do {
    	fread(label, 1, 2, src_file);
    	if(feof(src_file)) break;

        /* handles "code" headers */
    	if (label[0] == 0xCA && label[1] == 0xDE) {
            /* address read in */
            address = getc(src_file);
    		address = (address<<8) + getc(src_file);
            /* number of instructions read in */
    		fread(n, 1, 2, src_file);
    		int numInstructions = combine(n[0], n[1]); 
            /* loops per number of instructions and makes a new node for each */
    		int i;
    		for (i = 0; i < numInstructions; i+=1){
    			short unsigned int instruction;
    			instruction = getc(src_file);
                instruction = (instruction<<8) + getc(src_file);
    			//do i need struct before this function call??
    			head = add_to_list(head, address, instruction);
    			address += 0x1;
    		}
    	}

        /* handles "data" headers */
    	if (label[0]== 0xDA){
            /* address read in */
    		address = getc(src_file);
            address = (address<<8) + getc(src_file);
            /* number of instructions read in */
            fread(n, 1, 2, src_file);
    		int numInstructions = combine(n[0], n[1]); 
            /* loops per number of instructions and makes a new node for each */
    		int i;
    		for (i = 0; i < numInstructions; i+=1){
    			short unsigned int instruction;
                instruction = getc(src_file);
                instruction = (instruction<<8) + getc(src_file);
                head = add_to_list(head, address, instruction);
    			address += 1;
    		}
    	}
        
        /* handles "symbol" headers */
    	if (label[0] == 0xC3){
            /* address read in */
    		address = getc(src_file);
            address = (address<<8) + getc(src_file);
            /* number of characters in the label read in as "numInstructions" */
            fread(n, 1, 2, src_file);
    		int numInstructions = combine(n[0], n[1]); 
    		/* create space for a char array of the size numInstructions and add 1 for the endsign */
    		char * stuff = (char*)malloc(numInstructions + 1);
    		/* read in numInstructions bytes, add NULL terminator */
    		fread(stuff, 1, numInstructions, src_file);
            stuff[numInstructions] = '\0';
    		/* create row_of_mem pointer to holder node retuned from search, look for node with this address */
    		struct row_of_memory * nodeToEdit = search_address(head, address);
            /* check for NULL, if there is not yet a node with that address in the list, create one */
            if (nodeToEdit == NULL){
                head = add_to_list(head, address, 0);
                nodeToEdit = search_address(head, address);
            }
            /* edit the label field of the node at the address */
            nodeToEdit->label = stuff;
    	}
    } while (1);

    /* close file and check to make sure it closed properly */
	if (fclose(src_file) != 0){
		fprintf(stderr, "Error occurred while closing file. Memory freed.");
		delete_list(*memory);
    	return 2;
    }

    /* return the reference from head to memory to update */
    *memory = head;
	return 0 ;
}
