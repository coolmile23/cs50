#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[10];
	struct student *next;
}node;

//extern int insert_node(node *head, int id);
//extern int delete_node(node *head, int id);

#endif
