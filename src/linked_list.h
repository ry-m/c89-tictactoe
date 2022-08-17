#pragma once

typedef struct Node {
	void* data; 
	struct Node* next;
} Node; 

typedef struct {
	Node* head;
	Node* tail;
	int count;
} LinkedList;

typedef void (*print_func)(void*);

/* Forward declarations */

void new_list(LinkedList* list);
void insert_start(LinkedList* list, void* data);
void* remove_start (LinkedList* list);
void insert_last(LinkedList* list, void* data);
void* remove_last (LinkedList* list);
void disp(LinkedList* list, print_func pf);
void free_list(LinkedList* list);
