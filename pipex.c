/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/11 19:58:00 by athonda          ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	pid = fork();
	if (pid == 0)
	{
		fd = open("./test.txt", O_WRONLY);
		dup2(fd, 1);
		if (execve("/usr/bin/ls", argv, envp) == -1)
			_exit (0);
	}
	else if (pid > 0)
	{
		wait(&status);
		printf("wait for end of child process\n");
	}
	return (0);
}