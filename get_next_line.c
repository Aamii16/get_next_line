#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	buffer[100];
	int r = read(fd, buffer, 5);
	printf("test %d\n", r);
	return (buffer);
}
int main()
{
	int fd= open("token", 'r');
	char	  *buffer=get_next_line(fd);
	printf("buff %s", buffer);
}
