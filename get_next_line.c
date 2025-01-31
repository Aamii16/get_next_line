/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amzahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:06:22 by amzahir           #+#    #+#             */
/*   Updated: 2025/01/31 00:06:26 by amzahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	ft_memcpy(new_buffer, new_buffer + j, BUFFER_SIZE - j);
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
	static char		*buffer;
	char			*line;
	int				r;
	unsigned int	size;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
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
		line = strjoin(ft_strdup(""), buffer);
	r = read_file(&line, &buffer, fd);
	if ((r == 0 && buffer[0] == 0) || r == -1)
		return (free(buffer), buffer = NULL, line);
	return (line);
}
