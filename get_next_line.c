#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 5

char	*strjoin(char *line, char *new_buffer)
{
	int	i;
	int	j;
	char	*tmp_line;

	i = 0;
	j = 0;
	tmp_line = line;
	while (line[i])
		i++;
	while (new_buffer[j] && new_buffer[j] != '\n')
		j++;
	line = malloc (i + j);
	if (!line)
		return (NULL);
	i = -1;
	j = 0;
	while (tmp_line[++i])
		line[i] = tmp_line[i];
	while (new_buffer[j] && new_buffer[j] != '\n')
	{
		line[i + j] = new_buffer[j];
		j++;
	}
	free (tmp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;

	i = 0;
	buffer = malloc(BUFFER_SIZE);
	line = malloc(BUFFER_SIZE);
	if (!buffer || !line)
		return (NULL);
	read(fd, buffer, BUFFER_SIZE);
	line = strjoin(line, buffer);
	printf("test--%s--test %d\n", line, i);	
	while(!strchr(buffer, '\n'))
	{
		printf("---buffer %s---\n", buffer);

		if(read(fd, buffer, BUFFER_SIZE))
			line = strjoin(line, buffer);
		printf("---buffer %s---\n", buffer);
		break;
		//printf("test--%s--test %d\n", line, i);
	}
	printf("---------buffer %s---\n", buffer);
	return (line);
}
int main()
{
	int fd= open("test.txt", 'r');
	char	  *buffer=get_next_line(fd);
	printf("line  %s-----\n", buffer);
	//buffer=get_next_line(fd);
	//printf("buff %s----\n", buffer);
}
