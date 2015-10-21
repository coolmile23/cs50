#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	int id;
	char name[10];
	struct student *next;
}node;

int init_node(node *head);

int main(int argc, char **argv)
{
	node *s1 = NULL;
	node *s2 = NULL;
	node *s3 = NULL;
	node *head = NULL;

	init_node(head);

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
}


int init_node(node *head)
{
	if ((head = (node *)malloc(sizeof(node))) == NULL) {
		fputs("init node error.\n", stderr);
		return 1;
	}
	head->next = NULL;
	return 0;
}

int inset_node(node *head, node *insert_node, int id)
{
	
}

int delete_node()
{

}
