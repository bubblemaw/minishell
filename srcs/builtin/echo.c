/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:49 by maw               #+#    #+#             */
/*   Updated: 2025/03/10 14:09:30 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(t_cmd *cmd)
{
	int flag_n;
	int i;

	i = 1;
	flag_n = 0;
	while (ft_strncmp(cmd->arg[i],"-n", 2) == 0)
	{
		flag_n = 1;
		i++;
	}
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
		if (cmd->arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}	
	if (flag_n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}


