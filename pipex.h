/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:42:48 by athonda           #+#    #+#             */
/*   Updated: 2024/08/23 22:10:17 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_count_words(char const *str, char delimiter);
void	ft_cleanmem(unsigned int i, char **word);
int		ft_setstr(char const *s, char c, size_t nbr_words, char **word);
char	**ft_split(char const *s, char c);
void	free_split(char **str);
void	error_exit(char *str);
void	error_empty_cmd(char **cmd_parts);
void	error_wrong_cmd(char **cmd_parts);
void	wait_all(void);
char	**find_envpath(char **envp);
char	*join_cmd_path(char *cmd, char *path);
char	*get_fullpath(char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);
void	child(char **argv, char **envp, int *pipfd);
void	parent(char **argv, char **envp, int *pipfd);
void	sub_stream(int pipfd[3], char **argv, int argc, int loop);
void	main_stream(int pipfd[3], int argc, int i);
int		pipex(int argc, char **argv, char **envp);
int		pipex_bonus(int argc, char **argv, char **envp);
#endif //PIPEX_H