/*insist on*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "linked_list.h"

#define NUMBER_SIZE 		200000
#define RANDOM_NUMBER_RANGE 	100000
#define RANDOM_NUMBER_BASE	100000

int insert_node(node *head, int index_id, int id, char *name);
int get_num(int sort[], int num);
int generate_random_num(int num[], int num_size, int base_num, int num_range);
int generate_random_num_file(char *file_name, int num[], int number_size, int num_range);
int get_random_num_from_file(char *file_name, int num_buf[], int num_counter, int max_num_length);
int buble_sort(int sort[], int num_size);
int merge_sort(int sort[], int start_index, int end_index);
int statistic_num(int num[], int num_size, int num_range);
static int merge(int sort[], int start_index, int mid_index, int end_index);

int main(int argc, char **argv)
{
	int sort[NUMBER_SIZE] = {0};
	memset(sort, '\0', sizeof(sort));
	char *name[NUMBER_SIZE] = {"hi", "hello", "good", "day", "job"}; 

	int j = 0;
	for (j = 5; j < NUMBER_SIZE; j++) {
		name[j] = name[0];
	}
		
	FILE *fd = fopen("userdata.txt", "w+");

	node *head = NULL;
	
	if ((head = (node *)malloc(sizeof(node))) == NULL) {
		fputs("malloc fail.\n", stderr);
		return 1;
	}
	
	generate_random_num(sort, NUMBER_SIZE, RANDOM_NUMBER_BASE, RANDOM_NUMBER_RANGE);

	int temp_i;
	for (temp_i = 0; temp_i < NUMBER_SIZE; temp_i++) {
		insert_node(head, 0, sort[temp_i], name[temp_i]);
	}

	node *iterator_node = head->next;

	while (iterator_node != NULL) {
		printf("id:%-10d\tname:%s\n", iterator_node->id, iterator_node->name);
		fprintf(fd, "%d %s\n", iterator_node->id, iterator_node->name);
		iterator_node = iterator_node->next;
	}
	fclose(fd);

	

//	generate_random_num_file("random_num.txt", sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
//	printf("generate random num file done.\n sort: %s\n", sort);

/*	get_random_num_from_file("random_num.txt", sort, NUMBER_SIZE, 4);
	
	merge_sort(sort, 0, NUMBER_SIZE - 1);

	int i = 0;
	for (i = 0; i < NUMBER_SIZE; i++) {
		printf("%d\t", sort[i]);
	}
	printf("\n");
*/
//	buble_sort(sort_size);

//	statistic_num(sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
	return 0;
}

/* get random number from file.
 *
 * @file_name:	 	the name of file stored random number.
 * @num_buf:	 	for random number store.
 * @num_counter: 	get how many random number from file.
 * @max_num_length: 	a number's max length.
 */
int get_random_num_from_file(char *file_name, int num_buf[], int num_counter, int max_num_length)
{
	int fd;
	if ((fd = open(file_name, O_RDWR)) < 0) {
		fputs("open fail.\n", stderr);
		return 3;
	}

	int number_length = 0; 	 	  /* a number's length */
	char temp_buf[10];        	  /* for read() store */
	char number[max_num_length + 1];                  /* for temp number store, store a number */
	int number_get[num_counter + 1];      /* finally numbers get from file */
	int num_index = 0; 		  	  /* as index: the x th number */
	memset(temp_buf, '\0', 10);
	memset(number, '\0', max_num_length);
	memset(number_get, 0, sizeof(number_get));
	while (read(fd, temp_buf, 1) > 0) {
//		printf("char get: %s\n", store_buf);
		if (temp_buf[0] == '|' && number[0] != '\0') {
			number[number_length] = '\0';
			number_get[num_index] = atoi(number);
			num_index++;
//			printf("number get: %d\n", number_get[num]);
			memset(number, '\0', max_num_length);
			number_length = 0;
		} else if (temp_buf[0] >= '0' && temp_buf[0] <= '9') {
			number[number_length] = temp_buf[0];
			number_length++;
		}
	}
	close(fd);

	int i = 0;
	printf("GET NUMBER FROM FILE:\n");
	for (i = 0; i < num_index; i++) {
		printf("%d\t", number_get[i]);
	}
	printf("\n-------------------------------\n");

	return 0;	
}
 

/* generate random number and write into file.
 * @file_name:	file name
 * @num: 	number array to store in file.
 * @num_size:	array size.
 * @num_range:	number range to max.
 */
int generate_random_num_file(char *file_name, int num[], int num_size, int num_range)
{
	char *store_buf = NULL;
	FILE *fd = NULL;
	

	/* num_size for '|' store and 1 for '\0' */
	if ((store_buf = (char *)malloc(sizeof(int) * (num_size + 1) + 1)) == NULL) {
		fputs("malloc fail.\n", stderr);
		return 1;
	}
	memset(store_buf, '\0', sizeof(int) * (num_size + 1) + 1);
	
	if ((fd = fopen(file_name, "w+")) < 0) {
		fputs("fopen error.\n", stderr);
		return 2;
	}

	srandom(time(0));
	int iter = 0;
	for (iter = 0; iter < num_size; iter++) {
		num[iter] = random() % num_range;
	}

	printf("generated random num for file: \n");
	int counter = 0;
	for (iter = 0; iter < num_size; iter++) {
		printf("%d\t", num[iter]);
		counter++;
		if (counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	
	for (iter = 0; iter < num_size; iter++) {
		sprintf(store_buf, "%s|%d", store_buf, num[iter]);
	}

	printf("store buf =%s\n", store_buf);
	fputs(store_buf, fd);
	fclose(fd);

	free(store_buf);

	return 0;
}

/* generate random number and stored in num[]
 * @num_size: 	how many random number you want.
 * @num_range: 	the max random number.
 * @base_num:	the min random number.
 */
int generate_random_num(int num[], int num_size, int base_num, int num_range)
{
	int iter = 0;
	srandom(time(0));
	for (iter = 0; iter < num_size; iter++) {
		num[iter] = random() % num_range + base_num;
	}

	return 0;
}

int get_num(int sort[], int num)
{
	int iter = 0;

	printf("input %d numbers: \n", num);
	for (iter = 0; iter < num; iter++) {
		scanf("%d", &sort[iter]);
	}

	return 0;
}

/* buble sort 
 * @sort: 	array needed to be sorted.
 * @num_size:	how many number to sort.
 */
int buble_sort(int sort[], int num_size)
{
	int i = 0;
	int j = 0;
	int temp = 0;

	for (i = 0; i < num_size - 1; i++) { 
		for (j = 0; j < num_size - i - 1; j++) {
			if (sort[j] > sort[j + 1]) {
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}

	printf("\nbuble sort done: \n");
	int counter = 0;
	for (i = 0; i < num_size; i++) {
		printf("%d\t", sort[i]);
		if (++counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}

/* merge sort
 * input parameters:
 *      @sort: 		the array needed to be sorted
 *      @start_index: 	sorted from where
 *      @end_index: 	sort to where
 */
int merge_sort(int sort[], int start_index, int end_index)
{
	int mid_index = (start_index + end_index) / 2;

	if (start_index < end_index) {
		merge_sort(sort, start_index, mid_index);
		merge_sort(sort, mid_index + 1, end_index);
		merge(sort, start_index, mid_index, end_index);
	}

	return 0;
}

static int merge(int sort[], int start_index, int mid_index, int end_index)
{
	int temp_array[end_index - start_index + 1];
	int pos = 0;                /* position of temp_array's element*/
	int lpos = start_index;     /* position of left sub array */
	int rpos = mid_index + 1;   /* position of right sub array */

	memset(temp_array, 0, sizeof(temp_array));

	while (lpos <= mid_index && rpos <= end_index) {
		if (sort[lpos] < sort[rpos]) {
			temp_array[pos++] = sort[lpos++];
		} else {
			temp_array[pos++] = sort[rpos++];
		}
	}

	/* the left numbers must bigger than others */
	while (lpos <= mid_index) {
		temp_array[pos++] = sort[lpos++];
	}
	while (rpos <= end_index) {
		temp_array[pos++] = sort[rpos++];
	}
	/*******************************************/
	
	int iter = 0; /* iterator */
	for (iter = 0; iter < pos; iter++) {
		sort[start_index + iter] = temp_array[iter];
	}

	return 0;
}

int statistic_num(int num[], int num_size, int num_range)
{
	int temp_buf[num_range];
	int iterator = 0;
	int i = 0;

	memset(temp_buf, 0, sizeof(temp_buf));

	iterator = num_size - 1;
	while (iterator-- >= 0) {
		temp_buf[num[iterator]]++;
	}

	for (i = 0; i < num_range; i++) {
		printf("%d:\t%d\n", i, temp_buf[i]);
	}
	return 0;
}



/* insert a new node to linked list
 * @head:	linked list's head pointer
 * @index_id:	insert before this id, if index_id = 0, insert to the tail. 
 * @id:		insert node's id
 * @name:	insert node's name
 */
int insert_node(node *head, int index_id, int id, char *name)
{
	node *iterator = NULL;	
	node *new_node = NULL;


	iterator = head;

	/* id = 0 means insert into the linked list tail by default */
	if (index_id == 0) {
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
			
		if ((new_node = (node *)malloc(sizeof(node))) == NULL) {
			fputs("allocation fail.\n", stderr);
			return 1;
		}
/*
		printf("input id:");
		scanf("%d", &(new_node->id));	
		printf("input name:\n");
		scanf("%s", new_node->name);
*/
		new_node->id = id;
		memcpy(new_node->name, name, sizeof(new_node->name));

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
/*
				printf("input insert id:");
				scanf("%4d", &(new_node->id));	
				printf("input insert name:\n");
				scanf("%s", new_node->name);
*/
				new_node->id = id;
				memcpy(new_node->name, name, sizeof(new_node->name));

				iterator->next = new_node;	
				new_node->next = temp_node;
				break;
			}
			iterator = iterator->next;
		}
	}

	return 0;
}
