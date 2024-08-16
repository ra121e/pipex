/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/16 12:47:26 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, int *pipfd)
{
		close(pipfd[0]);
		if (dup2(pipfd[1], STDOUT_FILENO) < 0)
			perror("dup2 error in child");
		//close(pipfd[1]);
		exec_cmd(argv[1], envp);
}

void	parent(char **argv, char **envp, int *pipfd)
{
		close(pipfd[1]);
		if (dup2(pipfd[0], STDIN_FILENO) < 0)
			perror("dup2 error in parent");
		//close(pipfd[0]);
		printf("wait for end of child process\n");
		exec_cmd(argv[2], envp);
}

void	pipex(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipfd[2];

	(void)argc;
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
	//pid_t	pid;
	//int		pipfd[2];

	//if (argc != 5)
	//	return (0);
	pipex(argc, argv, envp);
	return (0);
}
