/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:12:55 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:28:18 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_cmd *cmd, t_shell *shell)
{
	int	n;
	int	i;

	i = 0;
	while (cmd->arg[i])
		i++;
	if (i == 0)
		return ;
	n = 0;
	if (i > 2)
	{
		printf("exit\n");
		error("too much argument");
		shell->exit_status = 1;
		return ;
	}
	if (is_arguments_digit(cmd->arg, shell) == 0)
		n = 2;
	else if (i == 2)
		n = ft_atoi(cmd->arg[1]);
	free_shell(shell);
	printf("exit\n");
	shell->exit_status = n;
	exit(n);
}

void	ft_exit_void(int n, t_shell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(n);
}

int	is_arguments_digit(char **tab, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if ((tab[i][j] >= '0' && tab[i][j] <= '9')
				|| tab[i][j] == '+' || tab[i][j] == '-')
				j++;
			else
			{
				error("numerical number necessary");
				shell->exit_status = 2;
				return (0);
			}
		}
		i++;
	}
	return (i);
}

void	put_exit_status(t_shell *shell)
{
	if (errno == 13)
		shell->exit_status = 126;
	else if (errno == 2)
		shell->exit_status = 127;
}
