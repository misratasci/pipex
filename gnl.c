/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:30:31 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 11:57:34 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static int	strlength(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i += 1;
	return (i);
}

char	*get_after_line(char *b)
{
	int			nl_ind;
	char		*s;

	nl_ind = get_line_length(b);
	s = write_until_ind(b, nl_ind, strlength(b));
	free(b);
	return (s);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		s1len;

	s1len = strlength(s1);
	str = (char *)malloc(s1len + strlength(s2) + 1);
	if (!str)
		return (NULL);
	if (!s1 && !s2)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (++i < s1len)
		str[i] = s1[i];
	i = -1;
	while (++i < strlength(s2))
		str[s1len + i] = s2[i];
	str[s1len + i] = 0;
	if (s1)
		free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*next_line;
	char		*next_buffer;

	while (1)
	{
		next_buffer = get_next_buffer(fd);
		if (!next_buffer)
		{
			free(saved);
			saved = NULL;
			return (NULL);
		}
		saved = ft_strjoin_gnl(saved, next_buffer);
		if (count_nls(next_buffer) != 0 || !next_buffer[0])
			break ;
		free(next_buffer);
		if (!saved)
			return (NULL);
	}
	free(next_buffer);
	next_line = get_until_nl(saved);
	saved = get_after_line(saved);
	return (next_line);
}
