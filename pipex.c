/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/20 13:04:20 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pipex.c
 * @brief run two shell commands by connected by pipe
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

void	child(char **argv, char **envp, int *pipfd)
{
	int	fd;

	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2 pipe write end -> standard out: error in child");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY, 0777);
	if (fd < 0)
		exit(1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 pipe read end -> standard IN: error in child");
		exit(1);
	}
	exec_cmd(argv[2], envp);
}

void	parent(char **argv, char **envp, int *pipfd)
{
	int	fd;

	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
	{
		perror("dup2 pipe read -> standard IN: error in parent");
		exit(1);
	}
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 pipe write -> standard OUT: error in parent");
		exit(1);
	}
	exec_cmd(argv[3], envp);
}

void	pipex(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipfd[2];

	(void)argc;
	if (pipe(pipfd) == -1)
	{
		perror("pip creation error");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		perror("fork error!");
	else if (pid == 0)
		child(argv, envp, pipfd);
	else if (pid > 0)
		parent(argv, envp, pipfd);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("need 4 arguments: ./pipex file command command file");
		return (0);
	}
	pipex(argc, argv, envp);
	return (0);
}
