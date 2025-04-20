/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:54:14 by david             #+#    #+#             */
/*   Updated: 2025/04/20 12:01:51 by masase           ###   ########.fr       */
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

	i = 0;
	tmp = NULL;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], "SHLVL", 5) == 0)
		{
			shell->lvl++;
			free(shell->env[i]);
			tmp = ft_strjoin("SHLVL=", ft_itoa(shell->lvl));
			shell->env[i] = tmp;
			return (0);
		}
		i++;
	}
	return (0);
}
