/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amzahir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:38:53 by amzahir           #+#    #+#             */
/*   Updated: 2025/01/31 00:38:59 by amzahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*cpy;

	len = 0;
	while (s1[len])
		len++;
	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	i = -1;
	while (s1[++i])
		cpy[i] = s1[i];
	cpy[i] = '\0';
	return (cpy);
}

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
