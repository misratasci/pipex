/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/11 16:23:45 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	int		i;
	int		*wstatus;
	int		wstat;

	if (argc != 5)
	{
		perror("parameters");
		exit(EXIT_FAILURE);
	}
	wstatus = &wstat;
	paths = get_cmd_paths(envp);
	pipex(argv, paths, wstatus);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	exit(WEXITSTATUS(wstat));
}
