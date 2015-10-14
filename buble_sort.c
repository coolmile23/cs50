#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_SIZE 5000
#define RANDOM_NUMBER_RANGE 10000

int get_num(int sort[]);
int buble_sort(int sort[]);
int generate_random_num(int num[], int num_size, int num_range);
int generate_random_num_file(char *file_name, int num[], int number_size, int num_range);
int get_random_num_from_file(char *file_name, int num_buf[], int num_counter);

int main(int argc, char **argv)
{
	int sort[NUMBER_SIZE] = {0};
	
	generate_random_num(sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
	generate_random_num_file("random_num.txt", sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
	memset(sort, '\0', sizeof(sort));
	get_random_num_from_file("random_num.txt", sort, NUMBER_SIZE);
	
	
	buble_sort(sort);

	return 0;
}

/*
 * get random number from file.
 * @num_buf: for random number store.
 * @num_counter: get how many random number from file.
 */
int get_random_num_from_file(char *file_name, int num_buf[], int num_counter)
{
	FILE *fd;
	char store_buf[1024 * 4];
	char *num_start = NULL;
	char *num_end  = NULL;

	while ((num_buf = malloc(1024 * 4)) == NULL) {
		fputs("malloc fail while get random number from file.\n", stderr);
		return 1;
	}

	memset(store_buf, '\0', 1024 * 4);

	if ((fd = fopen(file_name, "r")) < 0) {
		fputs("fopen error while get random num from file.\n", stderr);
		return 2;
	}

	fgets(store_buf, sizeof(store_buf), fd);
	num_start = strstr(store_buf, '-');
	num_end = strstr(num_start + 1, '-');
	memset(store_buf, '\0', sizeof(store_buf));
	printf("in the beginning, num_start pointer: %c\nnum_end pointer: %c\n", *num_start, *num_end);
	while (fgets(num_buf, sizeof(num_buf), fd) != NULL) {
		memcpy(store_buf, num_end - num_start, num_start);
		printf("store buffer: %s\n", store_buf);
		num_start = strstr(num_buf, '-');
		num_end = strstr(num_start + 1, '-');
		printf("num_start pointer: %c\nnum_end pointer: %c\n", *num_start, *num_end);
	}
	
	return 0;	
}
 
/*
 * generate random number and write into file.
 *  
 */
int generate_random_num_file(char *file_name, int num[], int num_size, int num_range)
{
	int i = 0;
	int counter = 0;
	char *store_buf = NULL;
	FILE *fd = NULL;
	
	if ((store_buf = malloc(1024 * 100)) == NULL) {
		fputs("malloc fail.\n", stderr);
		return 1;
	}
	
	if ((fd = fopen(file_name, "w+")) < 0) {
		fputs("fopen error.\n", stderr);
	}

	srandom(time(0));
	for (i = 0; i < num_size; i++) {
		num[i] = random() % num_range;
	}

	printf("generated random num for file: \n");
	for (i = 0; i < num_size; i++) {
		printf("%d\t", num[i]);
		counter++;
		if (counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	for (i = 0; i < num_size; i++) {
		sprintf(store_buf, "-%s-%d", store_buf, num[i]);
	}
	printf("store buf = %s\n", store_buf);
	fputs(store_buf, fd);
	fclose(fd);
	if (store_buf != NULL) {
		free(store_buf);
	}

	return 0;
}

/* generate random number and stored in num[]
 * @num_size: how many random number you want.
 * @num_range: the max random number.
 */
int generate_random_num(int num[], int num_size, int num_range)
{
	int i = 0;
	int counter = 0;

	srandom(time(0));
	for (i = 0; i < num_size; i++) {
		num[i] = random() % num_range;
	}

	printf("generated random num: \n");
	for (i = 0; i < num_size; i++) {
		printf("%d\t", num[i]);
		counter++;
		if (counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}

int get_num(int sort[])
{
	int loop_integer = 0;

	printf("input %d numbers: \n", NUMBER_SIZE);
	for (loop_integer = 0; loop_integer < NUMBER_SIZE; loop_integer++) {
		scanf("%d", &sort[loop_integer]);
	}

	return 0;
}

/* buble sort 
 *
 */
int buble_sort(int sort[])
{
	int i = 0;
	int j = 0;
	int temp = 0;
	int counter = 0;

	for (i = 0; i < NUMBER_SIZE - 1; i++) { 
		for (j = 0; j < NUMBER_SIZE - i - 1; j++) {
			if (sort[j] > sort[j + 1]) {
				temp = sort[j];
				sort[j] = sort[j + 1];
				sort[j + 1] = temp;
			}
		}
	}

	for (i = 0; i < NUMBER_SIZE; i++) {
		printf("%d\t", sort[i]);
		if (++counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}
