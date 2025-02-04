/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amzahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:41:50 by amzahir           #+#    #+#             */
/*   Updated: 2025/01/31 00:41:53 by amzahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

void	*ft_memcpy(char *d, char *s, size_t size);
char	*ft_strchr(const char *s, int n);
char	*join_buffer(char *line, char *new_buffer);
int		read_file(char **line, char	**buffer, int fd);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);

#endif
