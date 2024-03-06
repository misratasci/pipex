/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/06 15:11:53 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *file1, char *cmd1, char *cmd2, char *file2)
{
	pid_t	pid;
	int		fd;
	int		pipefd[2];
	char	reading_buf[1];

	fd = open(file1, O_RDONLY, 0777);
	if (fd == -1)
		perror(file1);
	if (pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(cmd1);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		int outfd = open(file2, O_WRONLY | O_CREAT, 0777);
        while(read(pipefd[0], reading_buf, 1) > 0)
            write(outfd, reading_buf, 1);
        close(pipefd[0]);
	}
}

void	exec_cmd(char *cmd)
{
	char	**argv;
	char	*cmdpath;
	size_t	i;

	argv = ft_split(cmd, ' ');
	cmdpath = ft_strjoin("/usr/bin/", argv[0]);
	if (access(cmdpath, X_OK) == -1)
		perror("access");
	execve(cmdpath, argv, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
	i = 0;
		while (argv[i])
			free(argv[i++]);
	free(argv);
	free(cmdpath);
}