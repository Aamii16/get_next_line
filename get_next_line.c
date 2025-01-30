#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define BUFFER_SIZE 1

void	*ft_memcpy(char *d, char *s, size_t size)
{
	if (!d || !s)
		return (NULL);
	while (size--)
		*(d++) = *(s++);
	*d = 0;
	return (d);
}

char	*ft_strchr(const char *s, int n)
{
	unsigned char	c;

	if (!s)
		return (NULL);
	c = (unsigned char)n;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == *s)
		return ((char *)s);
	return (NULL);
}

char	*strjoin(char *line, char *new_buffer)
{
	char	*tmp_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp_line = line;
	while (tmp_line && tmp_line[i])
		i++;
	while (new_buffer[j] && new_buffer[j] != '\n')
		j++;
	if (new_buffer[j] == '\n')
		j++;
	line = malloc(i + j + 1);
	if (!line)
		return (NULL);
	if (i)
		ft_memcpy(line, tmp_line, i);
	free (tmp_line);
	ft_memcpy(line + i, new_buffer, j);
	if (ft_strchr(new_buffer, '\n'))
		ft_memcpy(new_buffer, ft_strchr(new_buffer, '\n') + 1, BUFFER_SIZE - j);
	else
		ft_memcpy(new_buffer, new_buffer + j + 1, BUFFER_SIZE - j);
	return (line);
}

int	read_file(char **line, char	**buffer, int fd)
{
	int	r;

	r = 0;
	while (1)
	{
		if (ft_strchr(*line, '\n'))
			break ;
		r = read(fd, *buffer, BUFFER_SIZE);
		if (!r || r == -1)
			break ;
		(*buffer)[r] = 0;
		*line = strjoin(*line, *buffer);
	}
	return (r);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			r;
	unsigned int	size;

	size = (unsigned int)BUFFER_SIZE;
	r = 0;
	line = NULL;
	if (!buffer)
	{
		buffer = malloc(size + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = 0;
	}
	else if (buffer)
		line = strjoin(strdup(""), buffer);
	r = read_file(&line, &buffer, fd);
	if ((r == 0 && buffer[0] == 0) || r == -1)
		return (free(buffer), buffer = NULL, line);
	return (line);
}
int main()
{
	int fd = open("test.txt", 'r');
	char *line;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}	
}