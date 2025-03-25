/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:12:55 by maw               #+#    #+#             */
/*   Updated: 2025/03/24 15:58:28 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_exit(t_cmd *cmd, t_shell *shell)
{
	int n;
	int	i;
	int j;

	i = 1;
	while (cmd->arg[i])
	{
		j = 0;
		while (cmd->arg[i][j])
		{
			if (ft_isdigit(cmd->arg[i][j]) == 0)
			{
				error("numerical number necessary");
				return;
			}
			j++;
		}
		i++;
	}	
	n = 0;
	if (i > 2)
	{
		printf("exit\n");
		error("too much argument");
		return ;
	}	
	if (i == 2)
		n = ft_atoi(cmd->arg[1]);
	free_shell(shell);
	free(shell->input); 
	printf("exit\n");
	exit(n);
}
