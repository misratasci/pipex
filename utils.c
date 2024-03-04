/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:57 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/04 15:21:55 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd)
{
	char	**argv;
	char	*cmdpath;
	size_t	i;
	pid_t	pid;
	int		status;

	argv = ft_split(cmd, ' ');
	cmdpath = ft_strjoin("/bin/", argv[0]);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		execve(cmdpath, argv, NULL);
		perror(argv[0]);
		exit();
	}
	else
	{
		wait();
		i = 0;
		while (argv[i])
		free(argv[i++]);
		free(argv);
		free(cmdpath);
	}
	
}

void	redirect_input(char *file)
{
	int		fd;
	pid_t	pid;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror(file);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}