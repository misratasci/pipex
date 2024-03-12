/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:28 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 14:18:25 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	quote_in_str(char *s)
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

int	listlen(char **list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list[i])
		i++;
	return (i);
}

char	**join_lists(char **l1, char **l2)
{
	char	**list;
	int		i;

	if (l1 == NULL)
		return (l2);
	list = (char **)malloc((listlen(l1) + listlen(l2) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	i = 0;
	while (i < listlen(l1))
	{
		list[i] = l1[i];
		i += 1;
	}
	i = 0;
	while (i < listlen(l2))
	{
		list[listlen(l1) + i] = l2[i];
		i += 1;
	}
	list[listlen(l1) + i] = NULL;
	free(l1);
	free(l2);
	return (list);
}
