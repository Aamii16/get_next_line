#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 40

void	*ft_memcpy(char *d, char *s, size_t size)
{
	if (!d || !s)
		return (NULL);
	while (*s && size--)
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
	if (new_buffer[0] == '\n')
		j++;
	line = malloc(i + j + 1);
	if (i)
		ft_memcpy(line, tmp_line, i);
	free (tmp_line);
	ft_memcpy(line + i, new_buffer, j);
	ft_memcpy(new_buffer, new_buffer + j, BUFFER_SIZE);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			r;

	r = 0;
	line = NULL;
	if (buffer)
		line = strjoin(strdup(""), buffer);
	if (!buffer)
	{
		buffer = malloc((long) BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		buffer[0] = 0;
	}
	while (1)
	{
		if (ft_strchr(line, '\n'))
			break ;
		r = read(fd, buffer, BUFFER_SIZE);
		if ( r == -1 || (r == 0 && buffer[0] == 0))
			return (free(buffer), buffer = NULL, NULL);
		buffer[r] = 0;
		line = strjoin(line, buffer);
	}
	return (line);
}
int main()
{
	int fd = open("test.txt", 'r');
	char *line;
	line = get_next_line(fd);
	printf("%s--\n", line);
	free(line);
	line = get_next_line(fd);
	printf("%s--\n", line);
	free(line);
}