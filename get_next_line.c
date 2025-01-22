#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 40

void	*ft_memcpy(void *dst, void *src, int size)
{
	char	*d;
	char	*s;

	s = (char *)src;
	d = (char *)dst;
	if (!dst || !src)
		return (NULL);
	while (size-- && *s)
		*(d++) = *(s++);	
	*d = 0;
	return (dst);
}

char	*strjoin(char *line, char *new_buffer)
{
	int		i;
	int		j;
	char	*tmp_line;

	i = 0;
	j = 0;
	tmp_line = line;
	while (tmp_line[i])
		i++;
	while (new_buffer[j] && new_buffer[j] != '\n')
		j++;
	line = malloc (i + j);
	ft_memcpy(line, tmp_line, i);
	ft_memcpy(line + i, new_buffer, j + 1);
	free(tmp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			r;
	
	line = NULL;
	if (buffer)
		line = strjoin(strdup(""), buffer);
	if (!buffer)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
	}
	while (1)
	{
		if (!(r = read(fd, buffer, BUFFER_SIZE)))
		{
			free(buffer);
			break ;
		}
		buffer[r] = 0;
		if (!line)
			line = strdup("");
		line = strjoin(line, buffer);
		if (strchr(buffer, '\n'))
		{
			ft_memcpy(buffer, strchr(buffer, '\n') + 1, BUFFER_SIZE);
			break ;
		}
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
	//buffer=get_next_line(fd);
	//printf("line 2 %s----\n", buffer);
	free(buffer);
}
