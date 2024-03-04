/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:21 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/04 13:23:26 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
	
	if (argc != 5)
	{
		//bir hata ver hangi hataları vereceğine bak
		return (-1);
	}
	file1 = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	file2 = argv[4];

	printf("%s, %s, %s, %s", file1, cmd1, cmd2, file2);
	redirect_input(file1);
	exec_cmd(cmd1);
	
}