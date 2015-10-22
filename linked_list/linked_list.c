#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[10];
	struct student *next;
}node;

int insert_node(node *head, int id);
int delete_node(node *head, int id);

int main(int argc, char **argv)
{
	node *head = NULL;
	node *iterator = NULL;

	if ((head = (node *)malloc(sizeof(node))) == NULL) {
		fputs("init node error.\n", stderr);
		return 1;
	}
	head->id = 0;
	head->next = NULL;

	int iter = 0;
	for (iter = 0; iter < 3; iter++) {
		insert_node(head, 0);
	}

	printf("insert before number 22:\n");
	insert_node(head, 22);

	iterator = head;
	while (iterator->next != NULL) {
		iterator = iterator->next;
		printf("%d\t%s\n", iterator->id, iterator->name);
	}


	FILE *fd = NULL;

	if ((fd = fopen("user.db", "w+")) == NULL) {
		fputs("error while openfile.\n", stderr);
		return 2;
	}

	node *p = head;
	while (p != NULL) {
		printf("%d\t%s\n", p->id, p->name);
		fprintf(fd, "%d\t%s\n", p->id, p->name);
		p = p->next;	
	}
	delete_node(head, 22);
	printf("after delete number 22:\n");
	p = head;
	while (p != NULL) {
		printf("%d\t%s\n", p->id, p->name);
		fprintf(fd, "%d\t%s\n", p->id, p->name);
		p = p->next;	
	}

	fclose(fd);
	return 0;
}



int insert_node(node *head, int id)
{
	node *iterator = NULL;	
	node *new_node = NULL;


	iterator = head;

	/* id = 0 means insert into the linked list tail by default */
	if (id == 0) {
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
			
		if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
			fputs("allocation fail.\n", stderr);
			return 1;
		}

		printf("input id:");
		scanf("%4d", &(new_node->id));	
		printf("input name:\n");
		scanf("%s", new_node->name);

		iterator->next = new_node;
		new_node->next = NULL;
	} else { /* insert node befor id */
		while (iterator->next != NULL) {
			if (iterator->next->id == id) {
				node *temp_node = iterator->next;
				if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
					fputs("allocation fail.\n", stderr);
					return 1;
				}
				printf("input insert id:");
				scanf("%4d", &(new_node->id));	
				printf("input insert name:\n");
				scanf("%s", new_node->name);
				iterator->next = new_node;	
				new_node->next = temp_node;
				break;
			}
			iterator = iterator->next;
		}
	}

	return 0;
}

/* input linked list's head and which id to delete.
 * @head: linked list need to be process.
 * @id:	  the id of node to be deleted
 */ 
int delete_node(node *head, int id)
{
	node *iterator = NULL;

	iterator = head;

	while (iterator->next != NULL) {
		if (iterator->next->id == id) {
			if (iterator->next->next == NULL) {
				free(iterator->next);		
				iterator->next = NULL;
			} else {
				node *temp_node = iterator->next;
				iterator->next = temp_node->next;
				free(temp_node);
			}
		}
		iterator = iterator->next;
	}

	return 0;
}
