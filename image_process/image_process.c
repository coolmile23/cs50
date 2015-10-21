#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define image_name "s.png"
#define image_name2 "ss.png"

int main(void)
{
	int fd;
	int fd2;
	
	char buff[10];
	memset(buff, '\0', sizeof(buff));

	if ((fd = open(image_name, O_RDWR)) < 0) {
		fputs("open file error.\n", stderr);
		return 1;
	}

	if ((fd2 = open(image_name2, O_RDWR|O_CREAT, 0644)) < 0) {
		fputs("open file error.\n", stderr);
		return 1;
	}

	while ((n = open(fd, buf, sizeof(buff))) > 0) {
		write(fd, buf, n);
	}

	return 0;
}
