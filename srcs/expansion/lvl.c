/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:54:14 by david             #+#    #+#             */
/*   Updated: 2025/04/20 17:40:17 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lvl_shell(t_shell *shell)
{
	shell->lvl = get_shell_lvl(shell);
	lvl_up(shell);
	return (0);
}

int	get_shell_lvl(t_shell *shell)
{
	int	i;
	int	lvl;

	i = 0;
	lvl = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(shell->env[i] + 6);
			return (lvl);
		}
		i++;
	}
	return (0);
}

int	lvl_up(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*lvl;

	i = 0;
	tmp = NULL;
	lvl = NULL;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], "SHLVL", 5) == 0)
		{
			shell->lvl++;
			free(shell->env[i]);
			lvl = ft_itoa(shell->lvl);
			tmp = ft_strjoin("SHLVL=", lvl);
			free(lvl);
			shell->env[i] = tmp;
			return (0);
		}
		i++;
	}
	return (0);
}
