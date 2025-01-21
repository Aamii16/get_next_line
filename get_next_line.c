#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 5

void	*ft_memcpy(void *dst, void *src, int size)
{
	char	*d;
	char	*s;

	s = (char *)src;
	d = (char *)dst;
	if (!dst || !src)
		return (NULL);
	while (size--)
		*(d++) = *(s++);	
	*d = 0;
	return (dst);
}

char	*strjoin(char *line, char *new_buffer, int *j)
{
	int	i;
	char	*tmp_line;

	i = 0;
	*j = 0;
	tmp_line = line;
	while (tmp_line[i])
		i++;
	while (new_buffer[*j] && new_buffer[*j])
		(*j)++;
	line = malloc (i + *j);
	i = -1;
	*j = 0;
	while (tmp_line[++i])
		line[i] = tmp_line[i];
	while (new_buffer[*j])
	{
		line[i + *j] = new_buffer[*j];
		(*j)++;
		if (new_buffer[*j] == '\n')
		{
			line[i + *j] = new_buffer[*j];
			(*j)++;
			break ;
		}			
	}
	line [i + *j + 1] ='\0';
	free(tmp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int	pos;
	
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE);
		if (!buffer)
			return (NULL);
	}
	line = strjoin(strdup(""), buffer, &pos);
	/*if (!read(fd, buffer, BUFFER_SIZE))
	{
		free (buffer);
		break ;
	}*/
	line = strjoin(line, buffer, &pos);
	while (!strchr(line, '\n'))
	{
		if (!read(fd, buffer, BUFFER_SIZE))
		{
			free (buffer);
			break ;
		}
		line = strjoin(line, buffer, &pos);
		if (strchr(buffer, '\n'))
			ft_memcpy(buffer, buffer + pos, pos);
	
	}
	return (line);
}
int main()
{
	int fd= open("test.txt", 'r');
	char	  *buffer=get_next_line(fd);
	
	printf("line  %s-----\n", buffer);
	buffer=get_next_line(fd);
	printf("line 2 %s----\n", buffer);
}
