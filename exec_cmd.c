/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:28:26 by athonda           #+#    #+#             */
/*   Updated: 2024/08/23 20:46:54 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec_cmd.c
 * @brief apply command on execve
 */

#include "pipex.h"

/**
 * @fn void	exec_cmd
 * @brief do execve
 * @param[in] cmd command in command line argment as argv[0]
 * @param[in] envp
 * @return none
 */

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_parts;
	char	*cmd_exe;

	cmd_parts = ft_split(cmd, ' ');
	if (cmd_parts == NULL)
		exit(EXIT_FAILURE);
	if (cmd_parts[0] == NULL)
	{
		ft_putstr_fd("pipex: Permission denied:\n", 2);
		free_split(cmd_parts);
		exit(126);
	}
	execve(cmd_parts[0], cmd_parts, envp);
	cmd_exe = get_fullpath(cmd_parts[0], envp);
	if (cmd_exe == NULL)
	{
		ft_putstr_fd(cmd_parts[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(cmd_parts);
		exit(127);
	}
	execve(cmd_exe, cmd_parts, envp);
	perror(cmd_parts[0]);
	free(cmd_exe);
	free_split(cmd_parts);
	exit(EXIT_FAILURE);
}
