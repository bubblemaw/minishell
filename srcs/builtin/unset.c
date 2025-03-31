/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:03:17 by maw               #+#    #+#             */
/*   Updated: 2025/03/27 16:10:32 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset(t_cmd *cmd, t_shell *shell)
{
	int i;
	int	j;

	j = 1;
	while (cmd->arg[j])
	{
		i = 0;
		while (shell->env[i] && strncmp(shell->env[i], cmd->arg[j], ft_strlen_to_equal(cmd->arg[j])) != 0)
			i++;
		if (shell->env[i] != NULL)
			slide_tab(shell->env, i);
		j++;
	}
	return (VALID);
}

int ft_strlen_to_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int slide_tab(char **tab, int i)
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
