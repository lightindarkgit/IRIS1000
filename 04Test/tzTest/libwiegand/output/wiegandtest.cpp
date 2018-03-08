#include <stdio.h>
#include <string.h>
#include "wiegandrw.h"

int main(int argc,char*argv[])
{
	int hid,pid;
	wiegandrw* wiegand = new wiegandrw();
//	int res = wiegand->wiegandread(hid,pid);
//	if(!res)
//	{
//		printf("read sucess!\n");
//		printf("hid = %d,pid = %d\n",hid,pid);
//	}
//	else
//	{
//		printf("read failed!\n");
//	}

	if(!wiegand->wiegangwrite("12312345",MODE_DECIMAL))
	{
		printf("write success!\n");
		wiegand->wiegandread(hid,pid);
	}
	else
	{
		printf("write failed!\n");
	}
	return 0;
}
