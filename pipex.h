/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:35 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/04 12:35:11 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	exec_cmd(char *cmd);
void	redirect_input(char *file);