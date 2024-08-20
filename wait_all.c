/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:50:34 by athonda           #+#    #+#             */
/*   Updated: 2024/08/20 22:13:39 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_all(void)
{
	pid_t	pid;
	int		wstatus;
	int		i;

	i = 0;
	while ((pid = waitpid(-1, &wstatus, 0)) > 0)
		i++;
}