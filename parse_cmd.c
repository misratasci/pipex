/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:17:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/13 12:16:53 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**handle_quotes(char *cmd, char q)
{
	char	**list;
	char	**split;
	int		i;
	int		el_count;

	list = ft_split_quotes(cmd, q);
	if (!list)
		return (NULL);
	el_count = listlen(list);
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
	free_list(list);
	return (split);
}

char	**parse_cmd(char *cmd)
{
	char	**split;

	if (includes(cmd, '/') && ft_strnstr(cmd, ".sh", ft_strlen(cmd)))
	{
		split = (char **)malloc(2 * sizeof(char **));
		split[0] = cmd;
		split[1] = NULL;
		return (split);
	}
	split = NULL;
	if (quote_in_str(cmd) == 1)
		split = handle_quotes(cmd, '\'');
	else if (quote_in_str(cmd) == 2)
		split = handle_quotes(cmd, '"');
	else
		split = ft_split(cmd, ' ');
	return (split);
}
