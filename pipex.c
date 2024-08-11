/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:36:32 by athonda           #+#    #+#             */
/*   Updated: 2024/08/11 13:06:09 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

extern char	**environ;

int main(int argc, char **argv, char **envp)
{
	char	*ptr[3];

	(void)argc;
	(void)argv;
	ptr[0] = ""; //"cat"でも"./a.out"でも何でも良い
	ptr[1] = "test.txt";
	ptr[2] = NULL;
	printf("process ID: %d\n", getpid());
	printf("environment variable: %s\n", environ[0]);
	execve("/usr/bin/cat", ptr, envp);
	printf("process ID: %d\n", getpid());
	return (0);
}