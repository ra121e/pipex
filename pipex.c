/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/13 13:26:35 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *pipfd)
{
		close(pipfd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		//close(pipfd[1]);
		if (execve("/usr/bin/ls", argv, envp) == -1)
		{
			perror("execve error in child");
		}
}

void	parent(char **argv, char **envp, int *pipfd)
{
		close(pipfd[1]);
		dup2(pipfd[0], STDIN_FILENO);
		//close(pipfd[0]);
		printf("wait for end of child process\n");
		if (execve("/usr/bin/wc", argv, envp) == -1)
			perror("execve error in parent");

}

void	pipex(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipfd[2];

	if (pipe(pipfd) == -1)
		perror("pip creation error");
	pid = fork();
	if (pid < 0)
		perror("fork error!");
	else if (pid == 0)
		child(argv, envp, pipfd);
	else if (pid > 0)
		parent(argv, envp, pipfd);

}

int main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipfd[2];

	//if (argc != 5)
	//	return (0);
	pipex(argc, argv, envp);
	return (0);
}