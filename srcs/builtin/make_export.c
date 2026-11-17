/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:06:09 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/23 09:38:13 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	make_export(t_shell *shell, t_cmd *current, t_token *tmp, int *j)
{
	while (current->arg[*j] != NULL)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
		{
			if (compare_with_env(shell, tmp) == ERROR)
				add_export(shell, tmp);
			tmp = tmp->next;
			(*j)++;
		}
		else if (tmp->type == NAME && var_name_export(tmp->value) == ERROR)
		{
			error_export(tmp->value, shell);
			tmp = tmp->next;
			(*j)++;
		}
		else
		{
			compare_with_export_tab(shell, current->arg[*j]);
			check_double_export(current->arg[*j], shell);
			tmp = tmp->next;
			(*j)++;
		}
	}
	return ;
}

int	compare_with_env(t_shell *shell, t_token *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		if (ft_strncmp(tmp->value, shell->env[i], j) == 0)
		{
			return (VALID);
		}
		i++;
	}
	return (ERROR);
}

int	compare_with_export_tab(t_shell *shell, char *var)
{
	int	i;
	int	j;

	i = 0;
	if (shell->export != NULL)
	{
		while (shell->export[i] != NULL)
		{
			j = 0;
			while (var[j] != '=')
				j++;
			if (ft_strncmp(var, shell->export[i], j) == 0)
			{
				slide_tab(shell->export, i);
				return (VALID);
			}
			i++;
		}
	}
	return (ERROR);
}
