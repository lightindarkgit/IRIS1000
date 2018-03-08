#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
int main(int argc ,char *argv[])
{
 int f0;
 f0 = open("/dev/tty0", O_RDWR);
 write(f0, "\033[9;0]", 8);
 close(f0);
 return 0;
}
