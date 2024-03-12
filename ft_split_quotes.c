/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:21:34 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 11:15:25 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_start_of_quote(const char *s, size_t i, char c)
{
	return (s[i] != c && (i == 0 || (s[i - 1] == c && s[i - 2] != '\\')));
}

int	is_quote(const char *s, size_t i, char c)
{
	return (s[i] == c && s[i - 1] != '\\');
}

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	res;

	if (!s[0])
		return (0);
	i = 0;
	res = 0;
	while (s[i])
	{
		if (is_start_of_quote(s, i, c))
			res++;
		i++;
	}
	return (res);
}

static size_t	count_letters(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (!is_quote(s, i, c) && s[i] != '\0')
		i++;
	return (i);
}

static char	*write_word(const char *s, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(count_letters(s, c) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (!is_quote(s, i, c) && s[i] != '\0')
	{
		if (s[i] == '\\')
		{
			i++;
			continue ;
		}
		str[j] = s[i];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	word;

	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		if (!is_quote(s, i, c) && (i == 0 || is_quote(s, i - 1, c)))
			arr[word++] = write_word(s + i, c);
		i++;
	}
	arr[word] = 0;
	return (arr);
}
