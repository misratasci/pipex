/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/06 20:01:26 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	strlength(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i += 1;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(strlength(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i += 1;
	}
	str[i] = 0;
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
/* 	char	**env; */
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	char	**paths;
/* 	int		i; */
/* 
	i = 0;
	while (envp[i])
		i++;
	env = malloc((sizeof(char *) * i) + 1);
	while(envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	} */
/* 	env[i] = NULL; */
	if (argc != 5)
	{
		perror("parameters");
		exit(EXIT_FAILURE);
	}
	file1 = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	file2 = argv[4];
	paths = get_cmd_paths(envp);
	pipex(file1, cmd1, cmd2, file2, paths);
	system("leaks pipex");
}
