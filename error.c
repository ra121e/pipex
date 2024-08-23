/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:46:53 by athonda           #+#    #+#             */
/*   Updated: 2024/08/22 07:54:29 by athonda          ###   ########.fr       */
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
