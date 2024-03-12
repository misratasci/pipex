/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:48:35 by mitasci           #+#    #+#             */
/*   Updated: 2024/03/12 14:49:10 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);
char	**ft_split_quotes(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*remove_esc_chars(const char *s, char c);
void	pipex(char **argv, char **envp, int *fd);
void	exec_cmd(char *cmd, char **envp);
char	**get_cmd_paths(char **envp);
char	*get_cmd_path(char *cmd, char **paths);
void	free_list(char **list);
int		quote_in_str(char *s);
int		listlen(char **list);
char	**join_lists(char **l1, char **l2);
char	**parse_cmd(char *cmd);
int		includes(char *s, char c);

#endif