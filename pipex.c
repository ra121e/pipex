/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/11 14:27:08 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

extern char	**environ;

int main(int argc, char **argv, char **envp)
{
	char	*ptr[3];
	pid_t	pid;
	int		status;

	(void)argc;
	(void)argv;
	ptr[0] = ""; //"cat"でも"./a.out"でも何でも良い
	ptr[1] = "test.txt";
	ptr[2] = NULL;
	printf("process ID: %d\n", getpid());
	printf("environment variable: %s\n", environ[0]);
	printf("This is the before fork\n");
	pid = fork();
	printf("This is the after fork\n");
	printf("process ID after fork: %d\n", getpid());
	if (pid == 0)
	{
		printf("This is the first in child process\n");
		printf("process ID in child: %d\n", getpid());
		execve("/usr/bin/cat", ptr, envp);
		printf("process ID in child after execve: %d\n", getpid());
		_exit(0);
	}
	else if (pid > 0)
	{
		wait(&status);
		printf("wait for end of child process\n");
	}
	return (0);
}