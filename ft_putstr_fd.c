/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:58:36 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/13 12:17:25 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	print_cmd_err(char *s)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
}
