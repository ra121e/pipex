/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/12 11:56:37 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	int		fd;
	int		pipfd[2];
	char	*p = "Hi pipe\n";

	(void)argc;
	(void)argv;

	pipe(pipfd);
	pid = fork();
	if (pid == 0)
	{
		close(pipfd[0]);
		write(pipfd[1], p, 8);
		//dup2(pipfd[1], STDOUT_FILENO);
		//close(pipfd[1]);
		//if (execve("/usr/bin/ls", argv, envp) == -1)
		//	_exit (0);
	}
	else if (pid > 0)
	{
		char	buf[2];
		ssize_t	len_check;

		close(pipfd[1]);
		//dup2(pipfd[0], STDIN_FILENO);
		//close(pipfd[0]);
		printf("wait for end of child process\n");
		while ((len_check = read(pipfd[0], buf, 1)) > 0)
		{
			write(1, buf, 1);
		}
		//char *argv[] = {"/usr/bin/cat", "-e"};
		//execve("/usr/bin/cat", argv, envp);
	}
	return (0);
}