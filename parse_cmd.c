/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:17:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 19:06:31 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	quote_in_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ('\'' == s[i])
			return (1);
		else if ('"' == s[i])
			return (2);
		i++;
	}
	return (0);
}

static int	count_elements(char **list)
{
	int i;

	if (!list)
		return (0);
	i = 0;
	while (list[i])
		i++;
	return (i);
}

static char	**join_lists(char **l1, char **l2)
{
	char	**list;
	int		i;

	if (l1 == NULL)
		return (l2);
	list = (char **)malloc((count_elements(l1) + count_elements(l2) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	i = 0;
	while (i < count_elements(l1))
	{
		list[i] = l1[i];
		i += 1;
	}
	i = 0;
	while (i < count_elements(l2))
	{
		list[count_elements(l1) + i] = l2[i];
		i += 1;
	}
	list[count_elements(l1) + i] = NULL;
	free(l1);
	free(l2);
	return (list);
}

static char	**add_element(char **list, char *el)
{
	int		i;
	char	**res;

	if (!list)
		return (NULL);
	i = 0;
	while (list[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (list[i])
	{
		res[i] = list[i];
		i++;
	}
	res[i] = ft_strdup(el);
	res[i + 1] = NULL;
	free(list);
	return (res);
}

static char	**handle_quotes(char *cmd, char q)
{
	char	**list;
	char	**split;
	int		i;
	int		el_count;
	
	list = ft_split(cmd, q);
	if (!list)
		return (NULL);
	el_count = count_elements(list);
	i = 0;
	split = NULL;
	while (list[i])
	{
		if (i % 2 == 0)
		{
			split = join_lists(split, ft_split(list[i], ' '));
			if (el_count - 1 > i)
				split = add_element(split, list[i + 1]);
		}	
		i++;
	}
	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (split);
}

char	**parse_cmd(char *cmd)
{
	char	**split;

	split = NULL;
	if (quote_in_str(cmd) == 1)
		split = handle_quotes(cmd, '\'');
	else if (quote_in_str(cmd) == 2)
		split = handle_quotes(cmd, '"');
	else
		split = ft_split(cmd, ' ');
	return (split);
}
