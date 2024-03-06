/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/06 20:05:36 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char *cmd, char **paths)
{
	char	**argv;
	char	*cmdpath;
	size_t	i;

	argv = ft_split(cmd, ' ');
	i = 0;
	while (paths[i])
	{
		cmdpath = ft_strjoin(paths[i++], "/");
		cmdpath = ft_strjoin(cmdpath, argv[0]);
		if (access(cmdpath, X_OK) == 0) 
			break;
	}
	if (access(cmdpath, X_OK) == -1)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
	execve(cmdpath, argv, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	free(cmdpath);
}

static int	ft_pipe(char *cmd, char **paths)
{
	int		pipefd[2];
	pid_t	pid;
	
	pid = fork();
	if (pipe(pipefd) == -1 || pid == -1)
	{
		perror("pipe or fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		//dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(cmd, paths);
		return (-1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		return (pipefd[0]);
	}
}

static void	write_to_file(int infd, int outfd)
{
	int		l;
	char	buf[1];

	l = 1;
	while (l != 0)
	{
		l = read(infd, buf, 1);
		if (l == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		write(outfd, buf, 1);
	}
}

void	pipex(char *file1, char *cmd1, char *cmd2, char *file2, char **paths)
{
	int		fd;
	int		fd2;
	int		fd3;
	int		outfd;

	fd = open(file1, O_RDONLY, 0777);
	if (fd == -1)
		perror(file1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd2 = ft_pipe(cmd1, paths);
	dup2(fd2, STDIN_FILENO);
	close(fd2);
	fd3 = ft_pipe(cmd2, paths);
	outfd = open(file2, O_WRONLY | O_CREAT, 0777);
	write_to_file(fd3, outfd);
}

char **get_cmd_paths(char **envp)
{
	int		i;
	char	**path;
	char	**paths;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i];
			break;
		}
		i++;
	}
	path = ft_split(path, '=');
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}