/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 14:49:26 by mitasci          ###   ########.fr       */
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

	if (includes(cmd, '/') && ft_strnstr(cmd, ".sh", ft_strlen(cmd)))
	{
		cmdpath = remove_esc_chars(cmd, 0);
		argv = (char **)malloc(2 * sizeof(char **));
		argv[0] = cmd;
		argv[1] = NULL;
	}
	else if (!ft_strnstr(cmd, ".sh", ft_strlen(cmd)))
	{
		paths = get_cmd_paths(envp);
		argv = parse_cmd(cmd);
		cmdpath = get_cmd_path(argv[0], paths);
	}
	else
		argv = NULL;
	execve(cmdpath, argv, envp);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(EXIT_FAILURE);
}
