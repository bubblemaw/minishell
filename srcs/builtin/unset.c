/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:03:17 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:28:50 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;
	int	k;

	j = 1;
	while (cmd->arg[j])
	{
		i = 0;
		while (shell->env[i])
		{
			k = 0;
			while (shell->env[i][k] != '=')
				k++;
			if (ft_strncmp(shell->env[i], cmd->arg[j], k) == 0
				&& cmd->arg[j][k] == '\0')
				slide_tab(shell->env, i);
			i++;
		}
		j++;
	}
	shell->exit_status = 0;
	return (VALID);
}

int	ft_strlen_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	slide_tab(char **tab, int i)
{
	while (tab[i])
	{
		if (tab[i + 1] == NULL)
			break ;
		free(tab[i]);
		tab[i] = ft_strdup(tab[i + 1]);
		i++;
	}
	free(tab[i]);
	tab[i] = NULL;
	return (VALID);
}
