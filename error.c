/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:46:53 by athonda           #+#    #+#             */
/*   Updated: 2024/08/23 20:58:22 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file error_exit.c
 * @brief perror and exit with failure
 */

#include "pipex.h"

/**
 * @fn void	error_exit(char *str)
 * @brief perror and exit
 * @param[in] *str error message
 * @return none
 */

void	error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_empty_cmd(char **cmd_parts)
{
	ft_putstr_fd("pipex: Permission denied:\n", 2);
	free_split(cmd_parts);
	exit(126);
}

void	error_wrong_cmd(char **cmd_parts)
{
	ft_putstr_fd(cmd_parts[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_split(cmd_parts);
	exit(127);
}