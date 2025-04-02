/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:12:55 by maw               #+#    #+#             */
/*   Updated: 2025/04/02 12:27:05 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	n;
	int	i;

	i = is_arguments_digit(cmd->arg);
	if (i == 0)
		return;
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
	g_exit_status = n;
	exit(n);
}

void	ft_exit_void(int n,t_shell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(n);
}
int	is_arguments_digit(char **tab)
{
	int	i;
	int	j;
	
	i = 1;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_isdigit(tab[i][j]) == 0)
			{
				error("numerical number necessary");
				return (0);
			}
			j++;
		}
		i++;
	}	
	return (i);
}
