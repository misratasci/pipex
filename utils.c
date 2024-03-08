/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 11:16:35 by mitasci          ###   ########.fr       */
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
		dup2(pipefd[1], STDOUT_FILENO);
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
	char	*line;

	line = get_next_line(infd);
	while (line)
	{
		write(outfd, line, ft_strlen(line));
		line = get_next_line(infd);
	}
}

void	pipex(char **argv, char **paths)
{
	int		fd;
	int		fd2;
	int		fd3;
	int		outfd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		perror(argv[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd2 = ft_pipe(argv[2], paths);
	dup2(fd2, STDIN_FILENO);
	close(fd2);
	fd3 = ft_pipe(argv[3], paths);
	outfd = open(argv[4], O_WRONLY | O_CREAT, 0777);
	write_to_file(fd3, outfd);
}

char **get_cmd_paths(char **envp)
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
			break;
		}
		i++;
	}
	path = ft_split(pathline, '=');
	pathline = path[1];
	free(path[0]);
	free(path);
	paths = ft_split(pathline, ':');
	return (paths);
}