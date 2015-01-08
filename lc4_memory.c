/* Ryan Smith */

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"


struct row_of_memory* add_to_list    (struct row_of_memory* head, 
				      short unsigned int address, 
				      short unsigned int contents) {
	/* takes in head pointer to a linked list: head
	   creates a new node with address & contents passed in
	   adds node to end of linked list pointed to by head
	   if list is empty, new node is now head
	   always returns head pointer */ 

	/* if head is null, fills it with the new info to begin the list. */
	if (head == NULL){
		head = (struct row_of_memory*)malloc(sizeof(struct row_of_memory));
		head->address = address;
		head->contents = contents;
		head->assembly = NULL;
		head->label = NULL;
		head->next = NULL;
		return head;
	}
	
	/* creates space for a new row_of_memory to be added to the list. */
	struct row_of_memory* newNode = (struct row_of_memory*)malloc(sizeof(struct row_of_memory));
	/* checks for errors . */
	if (newNode == NULL){
		printf("Error: could not allocate memory for a new node.");
		exit(1);
	}

	/* populates fields in newly allocated node w/ address&contents */
	newNode->address = address;
	newNode->contents = contents;
	newNode->assembly = NULL;
	newNode->label = NULL;
	newNode->next = NULL;

	/* if head->next == NULL, adds the new node appropriately */
	if(head->next == NULL){
		if (head->address < newNode->address){
			head->next = newNode;
			return head;
		}
		if (head->address > newNode->address){
			newNode->next = head;
			return newNode;
		}
    }
    /* creates currentNode and sets to head for looping through the list */
	struct row_of_memory *currentNode = head;
	/* loops until finding the appropriate place for the node, then adds it in */
	while (currentNode != NULL){
		if ((currentNode->address < newNode->address) && (currentNode->next == NULL || (newNode->address < currentNode->next->address))){
			newNode->next = currentNode->next;
			currentNode->next = newNode;
		}
		currentNode = currentNode->next;
	}

	return head ;   
}

struct row_of_memory* search_address (struct row_of_memory* head, 
				      short unsigned int address ) {

	/* traverse linked list, searching each node for "address"  */
	struct row_of_memory *currentNode = head;
	while (currentNode != NULL){
		if (currentNode->address == address){
			/* return pointer to node in list that matches */
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	/* return NULL if list is empty or if "address" isn't found */	 
	return NULL ;
}

struct row_of_memory* search_opcode(struct row_of_memory* head, short unsigned int opcode){
/* traverse linked list until node is found with matching opcode
   AND "assembly" field of node is empty */
/* return pointer to node in list that matches, uses bit masking and shifting to compare against opcode bits in instruction*/
/* return NULL if list is empty or if no matching nodes */

	struct row_of_memory* searchNode = head;
	while (searchNode -> next != NULL){
		if ((((searchNode -> contents) & (0b1111000000000000)) == (opcode<<12)) && (searchNode -> assembly == NULL)){
			return searchNode;
		}
		searchNode = searchNode -> next;
	}
	return NULL ;
}

void print_list (struct row_of_memory* head ) {

	/* lays out labels and then loops to print the entire contents of the list */
	struct row_of_memory * currentNode = head;

	printf("%-25s %-14s %-15s %s\n","<LABEL>","<ADDRESS>","<CONTENTS>","<ASSEMBLY>");
	while (currentNode != NULL){
		/* this makes sure that the address prints all 4 spaces with %04x */
		printf("%-25s %04x%-11s %04x%-11s %s\n", currentNode->label, currentNode->address, "",currentNode->contents, "", currentNode->assembly );
		currentNode = currentNode->next;
	}

	return;
}

struct row_of_memory* delete_list    (struct row_of_memory* head ) {

	/* delete entire list node by node */
	/* also deletes labels and assembly pointers from within nodes when applicable */

	/* creates currentNode and sets to head for looping through the list */
	struct row_of_memory *currentNode = head;
    struct row_of_memory *next;

    while (currentNode != NULL)
    {
       next = currentNode->next;
       if (currentNode->label != NULL){
       		free(currentNode->label);
       }
       if (currentNode->assembly != NULL){
       	   	free(currentNode->assembly);
       }
       free(currentNode);
       currentNode = next;
    }

	return currentNode ;
}
