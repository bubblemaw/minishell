/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:25:49 by maw               #+#    #+#             */
/*   Updated: 2025/03/25 13:49:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(t_cmd *cmd)
{
	int flag_n;
	int i;

	flag_n = 0;
	i = echo_option(cmd);
	if (i > 1)
		flag_n = 1;
	while (cmd->arg[i])
	{
		ft_putstr_fd(cmd->arg[i], STDOUT_FILENO);
		if (cmd->arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}	
	if (flag_n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (VALID);
}

int echo_option(t_cmd *cmd)
{
	int i;
	int j;
	int flag_n;

	i = 1;
	while (cmd->arg[i] && cmd->arg[i][0] == '-')
	{
		flag_n = 1;
		j = 1;
		while (cmd->arg[i][j])
		{
			if (cmd->arg[i][j] != 'n')
			{
				flag_n = 0;
				break;
			}
			j++;	
		}
		if (flag_n == 0)
			break;
		i++;
	}
	return (i);
}


