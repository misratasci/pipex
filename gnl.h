/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:31:10 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/08 19:28:33 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);
int		get_line_length(char *s);
char	*write_until_ind(char *b, int start, int ind);
char	*get_until_nl(char *b);
char	*get_next_buffer(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		count_nls(char *b);
char	*get_after_line(char *b);