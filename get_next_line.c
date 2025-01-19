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
	
	printf("test join ""%s"" \n", line);

	while (line[i])
		i++;
	j = 0;
	while (new_buffer[j] && new_buffer[j] != '\n')
		j++;
	tmp_line = line;
	line = malloc (i + j);
	if (!line)
		return (NULL);
	i = 0;
	while (line[i++])
		line[i] = tmp_line[i];
	j = 0;
	while (new_buffer[j] && new_buffer[j] != '\n')
		line[i + j] = tmp_line[j++];
	free (tmp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			len;
	int			i;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	read(fd, buffer, BUFFER_SIZE);
	len = BUFFER_SIZE;
	strjoin(line, buffer);
	printf("test ""%s"" test \n", line);
	while(!strchr(buffer, '\n'))
	{
		read(fd, buffer, BUFFER_SIZE);
	    strjoin(line, buffer);
	}
	return (line);
}
int main()
{
	int fd= open("test.txt", 'r');
	char	  *buffer=get_next_line(fd);
	printf("%s\n", buffer);
	//buffer=get_next_line(fd);
	//printf("buff %s", buffer);
}
