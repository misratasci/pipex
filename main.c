/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 19:26:20 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;

	if (argc != 5)
	{
		perror("parameters");
		exit(EXIT_FAILURE);
	}
	paths = get_cmd_paths(envp);
	pipex(argv, paths);
	//system("leaks pipex");
}
