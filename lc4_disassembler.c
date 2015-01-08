/* Ryan Smith */

#include <stdio.h>
#include "lc4_memory.h"
#include <string.h>
#include <stdlib.h>

short unsigned int adjustImmediate(short unsigned int potentialImm){
	potentialImm = 16 - (potentialImm & 0b0000000000001111);
	return potentialImm;
}

int reverse_assemble (struct row_of_memory* memory) {

	/* searches through list for opcode 0001 which indicates arithmetic. when a node */
	/* containing correct opcode and empty assembly field is found, uses switch to */
	/* determine what operation is taking place and edits the assembly field as appropriate */
	
	/*creates variable to loop through list, and loops through all elements until element==NULL is encountered */
	struct row_of_memory * head = memory;
	while(head != NULL){
		struct row_of_memory *returnedNode = search_opcode(head, 0001);
		if (returnedNode == NULL){
			break;
		}
		/* mallocs space bigger than the longest string to hold results*/
		char assemblyInfo[50];
		/* uses bit masking and bit shifting to extract information from bits in contents */
		short unsigned int returnRegister = (returnedNode->contents & 0b0000111000000000)>>9;
		short unsigned int rsRegister = (returnedNode->contents & 0b0000000111000000)>>6;
		short unsigned int operationType = returnedNode->contents & 0b0000000000111000;
		short unsigned int rtRegister = returnedNode->contents & 0b0000000000000111;
		short unsigned int potentialImm = returnedNode->contents & 0b0000000000011111;

		/* operationType switch, sees what operation is taking place using binary numbers, edits assembly field */
		switch (operationType) {
			case 0b0000000000000000:
				returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "ADD R%d, R%d, R%d", returnRegister, rsRegister, rtRegister)+1);
				strcpy(returnedNode->assembly, assemblyInfo);
				break;
			case 0b0000000000001000:
				returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "MUL R%d, R%d, R%d", returnRegister, rsRegister, rtRegister)+1);
				strcpy(returnedNode->assembly, assemblyInfo);
				break;
			case 0b0000000000010000:
				returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "SUB R%d, R%d, R%d", returnRegister, rsRegister, rtRegister)+1);
				strcpy(returnedNode->assembly, assemblyInfo);
				break;
			case 0b0000000000011000:
				returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "DIV R%d, R%d, R%d", returnRegister, rsRegister, rtRegister)+1);
				strcpy(returnedNode->assembly, assemblyInfo);
				break;
			default:
				if (potentialImm <= 15){
					returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "ADD R%d, R%d, %d", returnRegister, rsRegister, potentialImm)+1);
					strcpy(returnedNode->assembly, assemblyInfo);
					break;
				}
				else{
					potentialImm = adjustImmediate(potentialImm);
					returnedNode->assembly = (char*)malloc(sprintf(assemblyInfo, "ADD R%d, R%d, -%d", returnRegister, rsRegister, potentialImm)+1);
					strcpy(returnedNode->assembly, assemblyInfo);
					break;
				}
		}

		head = head->next;
	}	
	return 0 ;
}
