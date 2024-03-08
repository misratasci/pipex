/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:30:58 by mitasci           #+#    #+#             */
/*   Updated: 2024/02/06 17:15:18 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_buffer(int fd)
{
	char	*buffer;
	int		l;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	l = read(fd, buffer, BUFFER_SIZE);
	if (l == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[l] = '\0';
	return (buffer);
}

int	get_line_length(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (i);
}

int	count_nls(char *b)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (b && b[i])
	{
		if (b[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*write_until_ind(char *b, int start, int ind)
{
	char	*s;
	int		i;

	if (start >= ind)
		return (NULL);
	s = (char *)malloc((ind + 2 - start) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (start < ind)
	{
		s[i] = b[start];
		start++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_until_nl(char *b)
{
	int			nl_ind;
	char		*s;

	nl_ind = get_line_length(b);
	s = write_until_ind(b, 0, nl_ind);
	return (s);
}
