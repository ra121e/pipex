/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 09:43:45 by athonda           #+#    #+#             */
/*   Updated: 2024/08/18 10:24:37 by athonda          ###   ########.fr       */
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

void	child(char **argv, char **envp, int *pipfd)
{
	int	fd;

	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		perror("dup2 pipe write -> standard out: error in child");
	fd = open(argv[1], O_RDONLY, 0777);
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2 pipe read -> standard IN: error in child");
	exec_cmd(argv[2], envp);
}

void	parent(char **argv, char **envp, int *pipfd)
{
	int	fd;

	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		perror("dup2 pipe read -> standard IN: error in parent");
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("dup2 pipe write -> standard OUT: error in parent");
	exec_cmd(argv[3], envp);
}

void	pipex(int argc, char **argv, char **envp)
{
	pid_t	pid[31245];
	int		pipfd[2];
	int		*pipfd[2];
	int		i;
	int		wstatus;

	(void)argc;
	if (pipe(pipfd[0]) == -1)
		perror("pip creation error");
	pid[0] = fork();
	if (pid[0] < 0)
		perror("fork error!");
	else if (pid[0] == 0)
		child(argv, envp, pipfd[0]);
	else if (pid[0] > 0)
	{
		i = 1;
		while (i < argc)
		{
			if (pipe(pipfd[i]) == -1)
				perror("error desu");
			pid[i] = fork();
			if (pid[i] < 0)
				perror("fork error!");
			else if (pid[i] == 0)
				child_mid(argv, envp, pipfd[i], pipfd[i - 1]);
			else if (pid[i] > 0)
				waitpid(pid[i], &wstatus, WNOHANG);
		}
		i++;
}

int main(int argc, char **argv, char **envp)
{
	//pid_t	pid;
	//int		pipfd[2];

	if (argc != 5)
	{
		perror("need 4 arguments: ./pipex file command command file");
		return (0);
	}
	pipex(argc, argv, envp);
	return (0);
}
