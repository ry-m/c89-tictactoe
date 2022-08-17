#include <stdlib.h>
#include "linked_list.h"

void new_list(LinkedList* list) {
	list = (LinkedList*)malloc(sizeof(LinkedList));
	
	list->head = NULL;
	list->tail = NULL;
	list->count = 0; 
}

void insert_start(LinkedList* list, void* data) {
	/** Create a new node */
	Node* newNode; 
	Node* temp;
	newNode = (Node*)malloc(sizeof(Node));
	
	/** Add data to new node */
	newNode->data = data; 
	newNode->next = NULL;
	
	/** Check if list is empty */
	if(list->head == NULL) {
		/** It is, set head and tail to new node */
		list->head = newNode;
		list->tail = newNode;
	} else {
		/* It isn't, fix links */
		temp = list->head;
		list->head = newNode; 
		list->head->next = temp;
	}

	list->count++;
}

void* remove_start (LinkedList* list) {
	void* start_data = NULL;
	if (list->head != NULL) {
		/* Create a copy pointer to current head */
		Node* head_copy = list->head;
		list->head = list->head->next; 
		
		/* Grab the data from current head */
		start_data = head_copy->data;
		
		/* Now free it */
		free(head_copy);
		
		list->count--;
	} 
	
	return start_data;
}

void insert_last(LinkedList* list, void* data) {
	/* Create a new node */
	Node* new_node; 
	Node* temp;
	new_node = (Node*)malloc(sizeof(Node));
	
	/* Add data to new node */
	new_node->data = data; 
	new_node->next = NULL;
	
	/* Check if list is empty */
	if(list->tail == NULL) {
		/* It is, set head and tail to new node */
		list->tail = new_node;
		list->head = new_node;
	} else {
		/* It isn't, fix links */
		temp = list->tail;
		list->tail = new_node;
		temp->next = new_node;
	}

	list->count++;
}

void* remove_last(LinkedList* list) {
	void* last_data = NULL;
	Node* curr_temp;
	Node* p_temp;
	
	if (list->tail != NULL) {
		if (list->head->next == NULL) {
			/* One item in list, tail == head */
			last_data = list->head->data; 
			free(list->head);
			list->head = NULL;
		} else {
			p_temp = NULL; 
			curr_temp = list->head; 
			
			while (!(curr_temp->next == NULL)) {
				p_temp = curr_temp; 
				curr_temp = curr_temp->next; 
			}
			
			p_temp->next = NULL;
			last_data = curr_temp->data;
			free(curr_temp);
		}
	} 

	list->count--;
	
	return last_data;
}

void free_list(LinkedList* list) {
	int ii; 
	int list_count = list->count; 
	Node* temp = list->head;
	Node* next = temp->next; 
	
	for (ii = 1; ii <= list_count; ii++) {
		if (next != NULL) {
			next = temp->next; 
			if (temp->data != NULL) {
				free(temp->data);
			}

			free(temp);
			temp = next; 
		}
	}
	
	free(list);
}

void disp(LinkedList* list, print_func pf) {
	Node* current; 
	int ii;
	current = list->head; 

	/* For each item in the list, print the data */ 
	for (ii = 1; ii <= list->count; ii++)
	{
		pf(current->data);
		current = current->next; 
	}
}
