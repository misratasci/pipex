/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/11 16:23:06 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	write_to_file(int infd, int outfd)
{
	char	*line;

	line = get_next_line(infd);
	while (line)
	{
		ft_putstr_fd(line, outfd);
		free(line);
		line = get_next_line(infd);
	}
}

static int	ft_pipe(char *cmd, char **paths, int *wstatus)
{
	int		pipefd[2];
	pid_t	pid;
	int		pip;

	pip = pipe(pipefd);
	pid = fork();
	if (pip == -1 || pid == -1)
	{
		perror("pipe or fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(cmd, paths);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, wstatus, 0);
		close(pipefd[1]);
		return (pipefd[0]);
	}
}

void	pipex(char **argv, char **paths, int *wstatus)
{
	int		fd;
	int		fd2;
	int		fd3;
	int		outfd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		fd = open("temp", O_RDONLY | O_CREAT, 0777);
	}
	dup2(fd, STDIN_FILENO);
	outfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfd == -1)
		perror(argv[4]);
	fd2 = ft_pipe(argv[2], paths, wstatus);
	dup2(fd2, STDIN_FILENO);
	close(fd2);
	fd3 = ft_pipe(argv[3], paths, wstatus);
	write_to_file(fd3, outfd);
	close(fd);
	unlink("temp");
}

char	**get_cmd_paths(char **envp)
{
	int		i;
	char	*pathline;
	char	**paths;
	char	**path;

	pathline = NULL;
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
	path = ft_split(pathline, '=');
	pathline = path[1];
	free(path[0]);
	paths = ft_split(pathline, ':');
	free(path[1]);
	free(path);
	return (paths);
}
