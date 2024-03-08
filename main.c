/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 17:28:08 by mitasci          ###   ########.fr       */
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
	
	parse_cmd("1 2  \"a b c d\" 1 2 3 \"a b c \" 1  2 3  4 ");
	/*
	int i = 0;
	while (list[i])
		printf("%s\n", list[i++]);
	*/
	pipex(argv, paths);
	//system("leaks pipex");
}
