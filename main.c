/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 18:39:43 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_io(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	dup2(fd3, STDIN_FILENO);
	dup2(fd4, STDOUT_FILENO);
	close(fd3);
	close(fd4);
}

static void	close_files(int fd1, int fd2, int fd3, int fd4)
{
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
}

static int	*open_files(char **argv)
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	fd[0] = open(argv[1], O_RDONLY, 0777);
	if (fd[0] == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		fd[0] = open("temp", O_RDONLY | O_CREAT, 0777);
	}
	fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	pipex(char **argv, char **envp, int *fd)
{
	int		pipefd[2];
	pid_t	pid[2];
	int		wstatus;

	if (pipe(pipefd) == -1)
		perror("pipe");
	pid[0] = fork();
	if (pid[0] == 0)
	{
		redirect_io(fd[1], pipefd[0], fd[0], pipefd[1]);
		exec_cmd(argv[2], envp);
	}
	pid[1] = fork();
	if (pid[0] == -1 || pid[1] == -1)
		perror("fork");
	if (pid[1] == 0)
	{
		redirect_io(fd[0], pipefd[1], pipefd[0], fd[1]);
		exec_cmd(argv[3], envp);
	}
	close_files(pipefd[0], pipefd[1], fd[0], fd[1]);
	waitpid(pid[0], &wstatus, 0);
	waitpid(pid[1], &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
		exit(WEXITSTATUS(wstatus));
}

int	main(int argc, char **argv, char **envp)
{
	int	*fd;

	if (argc != 5)
	{
		perror("parameters");
		exit(EXIT_FAILURE);
	}
	fd = open_files(argv);
	pipex(argv, envp, fd);
	parse_cmd("grep a");
	free(fd);
	unlink("temp");
	//check leaks!!
}
