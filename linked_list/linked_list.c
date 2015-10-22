#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[10];
	struct student *next;
}node;

int insert_node(node *head, int id);

int main(int argc, char **argv)
{
	node *s1 = NULL;
	node *s2 = NULL;
	node *s3 = NULL;
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

	iterator = head;
	while (iterator->next != NULL) {
		iterator = iterator->next;
		printf("%d\t%s\n", iterator->id, iterator->name);
	}

/*
	printf("inited.\n");
	if ((s1 = (node *)malloc(sizeof(node))) == NULL) {
		fputs("malloc error.\n", stderr);
		return 1;
	}

	if ((s2 = (node *)malloc(sizeof(node))) == NULL) {
		fputs("malloc error.\n", stderr);
		return 1;
	}

	if ((s3 = (node *)malloc(sizeof(node))) == NULL) {
		fputs("malloc error.\n", stderr);
		return 1;
	}

	memcpy(s1->name, "mike", sizeof("mike"));
	s1->id = 10086;
	s1->next = NULL;

	head->next = s1;

	memcpy(s2->name, "jack", sizeof("jack"));
	s2->id = 10011;
	s2->next = NULL;
		
	s1->next = s2;

	memcpy(s3->name, "miles", sizeof("miles"));
	s3->id = 10088;
	s3->next = NULL;
	s2->next = s3;

	node *p;
	p = head->next;	
	
	FILE *fd = NULL;

	if ((fd = fopen("user.db", "w+")) == NULL) {
		fputs("error while openfile.\n", stderr);
		return 2;
	}

	while (p != NULL) {
		printf("%d\t%s\n", p->id, p->name);
		fprintf(fd, "%d\t%s\n", p->id, p->name);
		p = p->next;	
	}

	free(s1);
	free(s2);
	free(s3);
	fclose(fd);
	return 0;
*/

	

}



int insert_node(node *head, int id)
{
	node *iterator = NULL;	
	node *new_node = NULL;


	iterator = head;

/*	if (iterator->next == NULL) {
		if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
			fputs("allocation fail.\n", stderr);
			return 1;
		}
		printf("input id:\n");
		scanf("%d", &(new_node->id));	
		printf("input name:\n");
		scanf("%s", new_node->name);
		iterator->next = new_node;
		new_node->next = NULL;
		head = iterator;
	}
*/
	while (iterator->next != NULL) {
/*		if (iterator->next->id == id) {
			if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
				fputs("allocation fail.\n", stderr);
				return 1;
			}
			printf("input id:\n");
			scanf("%d", &(new_node->id));	
			printf("input name:\n");
			scanf("%s", new_node->name);
			iterator->next->next = new_node;	
			new_node->next = NULL;
		}
*/
		if (iterator->next->next != NULL) {
			iterator = iterator->next;
			continue;
		}
		break;
	}
	//if (iterator->next->id == id) {
		if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
			fputs("allocation fail.\n", stderr);
			return 1;
		}
		printf("input id:\n");
		scanf("%d", &(new_node->id));	
		printf("input name:\n");
		scanf("%s", new_node->name);
		if (iterator->next == NULL) {
			head->next = new_node;
		} else {
			iterator->next->next = new_node;	
		}
		new_node->next = NULL;
	//}

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
		if (iterator->id == id) {

		}
		iterator = iterator->next;
	}
}
