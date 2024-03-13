/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/13 12:19:12 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

int	includes(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

char	**get_cmd_paths(char **envp)
{
	int		i;
	char	*pathline;
	char	**paths;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pathline = envp[i];
			break ;
		}
		i++;
	}
	path = ft_substr(pathline, 5, ft_strlen(pathline) - 5);
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*cmdpath;
	int		i;

	i = 0;
	cmdpath = NULL;
	if (includes(cmd, '/'))
		return (cmd);
	while (paths[i])
	{
		cmdpath = ft_strjoin(paths[i++], "/");
		cmdpath = ft_strjoin(cmdpath, cmd);
		if (access(cmdpath, X_OK) == 0)
			break ;
		free(cmdpath);
	}
	return (cmdpath);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**argv;
	char	*cmdpath;
	char	**paths;

	argv = parse_cmd(cmd);
	if (includes(cmd, '/') && ft_strnstr(cmd, ".sh", ft_strlen(cmd)))
		cmdpath = remove_esc_chars(cmd, 0);
	else if (!ft_strnstr(cmd, ".sh", ft_strlen(cmd)))
	{
		paths = get_cmd_paths(envp);
		cmdpath = get_cmd_path(argv[0], paths);
	}
	else
		argv = NULL;
	if (access(cmdpath, F_OK) == 0 && access(cmdpath, X_OK) != 0)
	{
		perror(cmdpath);
		exit(EXIT_FAILURE);
	}
	execve(cmdpath, argv, envp);
	print_cmd_err(argv[0]);
	exit(127);
}
