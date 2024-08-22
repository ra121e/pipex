/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:43:45 by athonda           #+#    #+#             */
/*   Updated: 2024/08/22 08:49:22 by athonda          ###   ########.fr       */
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

void	sub_stream(int pipfd[3], char **argv, int argc, int loop)
{
	if (loop == 2)
	{
		pipfd[2] = open(argv[1], O_RDONLY, 0777);
		if (pipfd[2] == -1)
			perror(argv[1]);
	}
	else if (loop == (argc - 2))
		pipfd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_exit("dup2 pipe write -> standard out: error in child");
	close(pipfd[1]);
	if (dup2(pipfd[2], STDIN_FILENO) < 0)
		error_exit("dup2 pipe read -> standard IN: error in child");
	close(pipfd[2]);
	close(pipfd[0]);
}

void	main_stream(int pipfd[3], int argc, int i)
{
	if (i > 2)
		close(pipfd[2]);
	close(pipfd[1]);
	pipfd[2] = pipfd[0];
	if (i >= argc - 2)
		close(pipfd[2]);
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

int	pipex(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipfd[3];
	int		i;
	int		wstatus;

	i = 1;
	while (++i < argc - 1)
	{
		if (pipe(pipfd) == -1)
			error_exit("pip creation error");
		pid = fork();
		if (pid < 0)
			error_exit("fork error!");
		else if (pid == 0)
		{
			sub_stream(pipfd, argv, argc, i);
			exec_cmd(argv[i], envp);
		}
		else if (pid > 0)
			main_stream(pipfd, argc, i);
	}
	waitpid(pid, &wstatus, 0);
	wait_all();
	return (WEXITSTATUS(wstatus));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		perror("need more that 4 arguments: ./pipex file command command file");
		return (0);
	}
	return (pipex(argc, argv, envp));
}
