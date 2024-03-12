/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 09:34:07 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static char	*get_cmd_path(char *cmd, char **paths)
{
	char	*cmdpath;
	int		i;

	i = 0;
	cmdpath = NULL;
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

static void	exec_cmd(char *cmd, char **paths)
{
	char	**argv;
	char	*cmdpath;
	size_t	i;

	argv = parse_cmd(cmd);
	i = 0;
	cmdpath = get_cmd_path(argv[0], paths);
	execve(cmdpath, argv, NULL);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void	pipex(char **argv, char **paths, int *wstatus)
{
	int		fd[2];
	int		pipefd[2];
	pid_t	pid[2];

	fd[0] = open(argv[1], O_RDONLY, 0777);
	if (fd[0] == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		fd[0] = open("temp", O_RDONLY | O_CREAT, 0777);
	}
	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		perror(argv[4]);
	if (pipe(pipefd) == -1)
		perror("pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		perror("fork 1");
	else if (pid[0] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(argv[2], paths);
	}
	pid[1] = fork();
	if (pid[1] == -1)
		perror("fork 2");
	else if (pid[1] == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(argv[3], paths);
	}
	wait(wstatus);
	unlink("temp");
}
