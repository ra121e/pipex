/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:28:26 by athonda           #+#    #+#             */
/*   Updated: 2024/08/16 12:37:28 by athonda          ###   ########.fr       */
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
		return ;
	cmd_exe = get_fullpath(cmd_parts[0], envp);
	if (cmd_exe == NULL)
	{
		free_split(cmd_parts);
		perror("get_fullpath error! in exec_cmd()");
		return ;
	}
	if (execve(cmd_exe, cmd_parts, envp) == -1)
	{
		free(cmd_exe);
		free_split(cmd_parts);
		perror("execve error!");
		return ;
	}
}
