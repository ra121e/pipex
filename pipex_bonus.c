/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:43:45 by athonda           #+#    #+#             */
/*   Updated: 2024/08/19 15:39:43 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pipex_bonus.c
 * @brief run many shell commands connected by pipe
 */

#include "pipex.h"

/**
 * @fn void	child
 * @brief child process swich fd and call execute command function
 * @param[in] argv
 * @param[in] envp
 * @param[in] pipfd array of fd of pipe
 * @return none
 */

int	sub_stream(char *cmd, char **envp, int fd)
{
	pid_t	pid;
	int		pipfd[2];
	int		wstatus;

	if (pipe(pipfd) == -1)
		perror("pip creation error");
	pid = fork();
	if (pid < 0)
		perror("fork error!");
	else if (pid == 0)
	{
		if (dup2(pipfd[1], STDOUT_FILENO) < 0)
			perror("dup2 pipe write -> standard out: error in child");
		close(pipfd[1]);
		if (dup2(fd, STDIN_FILENO) < 0)
			perror("dup2 pipe read -> standard IN: error in child");
		close(fd);
		close(pipfd[0]);
		exec_cmd(cmd, envp);
	}
	else if (pid > 0)
	{
		close(pipfd[1]);
		waitpid(pid, &wstatus, WNOHANG);
	}
	return (pipfd[0]);
}

/*
void	parent(char **argv, char **envp, int *pipfd)
{
	int	fd;

	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		perror("dup2 pipe read -> standard IN: error in parent");
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 pipe write -> standard OUT: error in parent");
}
*/

void	pipex(int argc, char **argv, char **envp)
{
	int		i;
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	i = 2;
	while (i < argc - 1)
	{
		fd = sub_stream(argv[i], envp, fd);
		i++;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2 pipe read -> standard IN: error in the last");
	close(fd);
	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 pipe write -> standard OUT: error in the last");
	exec_cmd(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		perror("need more that 4 arguments: ./pipex file command command file");
		return (0);
	}
	pipex(argc, argv, envp);
	return (0);
}
