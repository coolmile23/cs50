#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUMBER_SIZE 500000
#define RANDOM_NUMBER_RANGE 1000

int get_num(int sort[]);
int buble_sort(int sort[]);
int generate_random_num(int num[], int num_size, int num_range);
int generate_random_num_file(char *file_name, int num[], int number_size, int num_range);
int get_random_num_from_file(char *file_name, int num_buf[], int num_counter);
int merge_sort(int sort[], int start_index, int end_index);
int merge(int sort[], int start_index, int mid_index, int end_index);

int main(int argc, char **argv)
{
	int sort[NUMBER_SIZE] = {0};
	int i = 0;
	
	generate_random_num(sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
//	sleep(5);
	generate_random_num_file("random_num.txt", sort, NUMBER_SIZE, RANDOM_NUMBER_RANGE);
	printf("generate random num file done.\n sort: %s\n", sort);
//	sleep(5);

//	memset(sort, '\0', sizeof(sort));
//	get_random_num_from_file("random_num.txt", sort, NUMBER_SIZE);
	printf("\nafter get sort:\n %s\n", sort);
	for (i = 0; i < NUMBER_SIZE; i++) {
		printf("%d\t", sort[i]);
	}
	printf("\n");
	
	merge_sort(sort, 0, NUMBER_SIZE);

	for (i = 0; i < NUMBER_SIZE; i++) {
		printf("%d\t", sort[i]);
	}
	printf("\n");

//	buble_sort(sort);

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

	int fd_low;
	char number[10];
	int num = 0;    /* as index: the x th number */
	int number_length = 0; /* a number's length */
	int number_get[1024];
	
	memset(number_get, '\0', sizeof(number_get));

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
	printf("store buffer: %s\n", store_buf);

	num_start = strstr((const char *)store_buf, "-");
	num_end = strstr((const char *)num_start + 1, "-");
	printf("in the beginning, num_start pointer: %s\nnum_end pointer: %s\n", num_start, num_end);

	memset(store_buf, '\0', sizeof(store_buf));
	if ((fd_low = open(file_name, O_RDWR)) < 0) {
		fputs("open fail.\n", stderr);
		return 3;
	}
	number_length = 0;
	while (read(fd_low, store_buf, 1) > 0) {
//		printf("char get: %s\n", store_buf);
		if (store_buf[0] >= '0' && store_buf[0] <= '9') {
			number[number_length] = store_buf[0];
			number_length++;
		} else if (store_buf[0] == '-') {
			number[number_length] = '\0';
			number_get[num] = atoi(number);
//			printf("number get: %d\n", number_get[num]);
			num++;
			memset(number, '\0', sizeof(number));
			number_length = 0;
		}
	}
	close(fd_low);

	int i = 0;
	for (i = 0; i < num; i++) {
		printf("%d\t", number_get[i]);
	}

	for (i = 0; i < num; i++) {
		num_buf[i] = number_get[i];
		printf("num_buf[%d] = %d\n", i, num_buf[i]);
	}
//	memcpy(num_buf, number_get, sizeof(num_buf));	
//	num_buf[0] = 22;
	printf("num bf: %s\n", num_buf);

/*	while ((fgets(store_buf, sizeof(store_buf), fd)) != NULL) {
		memcpy(store_buf, num_start, num_end - num_start);
		printf("store buffer: %s\n", store_buf);
		num_start = strstr((const char *)store_buf, "-");
		num_end = strstr((const char *)num_start + 1, "-");
		printf("num_start pointer: %c\nnum_end pointer: %c\n", *num_start, *num_end);
	}
*/
	
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
	
	sprintf(store_buf, "$");
	for (i = 0; i < num_size; i++) {
		sprintf(store_buf, "%s-%d", store_buf, num[i]);
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

	printf("\nbuble sort done: \n");
	for (i = 0; i < NUMBER_SIZE; i++) {
		printf("%d\t", sort[i]);
		if (++counter % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}

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

int merge(int sort[], int start_index, int mid_index, int end_index)
{
	int buffer[end_index - start_index + 1];
	int pos = 0;
	int lpos = start_index;
	int rpos = mid_index + 1;
	printf("lpos = %d\n", lpos);
	printf("rpos = %d\n", rpos);

	memset(buffer, 0, sizeof(buffer));

	while (lpos <= mid_index && rpos <= end_index) {
		if (sort[lpos] < sort[rpos]) {
			buffer[pos++] = sort[lpos++];
		} else {
			buffer[pos++] = sort[rpos++];
		}
	}

	/* the left numbers must bigger than others */
	while (lpos <= mid_index) {
		buffer[pos++] = sort[lpos++];
	}
	while (rpos <= end_index) {
		buffer[pos++] = sort[rpos++];
	}
	/*******************************************/
	
	int iter = 0;
	for (iter = 0; iter < pos; iter++) {
		sort[start_index + iter] = buffer[iter];
	}

	return 0;
}
