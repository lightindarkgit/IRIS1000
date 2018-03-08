#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char*argv[])
{
	char temp[] = "hello,abc!";
	int num = 0;
	int i = 0;
	int fd;
		fd = open("/dev/wiegand",O_RDWR);
        if(fd == -1)
		{
		printf("creat file wrong!");
		return 0;
	    }
	char wiegand[26] = {0};
//	while(1){
		printf("beginread\n");
	    num = read(fd,wiegand,26);
	    printf("the num is %d\n",num);
	    for(i = 0;i < 26;i++)
	    printf("%d",wiegand[i]);
		printf("\n");
//    }
	close(fd);
	return 0;
}
