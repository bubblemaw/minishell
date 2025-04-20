/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:06:09 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/20 19:31:22 by david            ###   ########.fr       */
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
			{
				printf("ya  pas double reuf \n");
				add_export(shell, tmp);
			}
			tmp = tmp->next;
			(*j)++;
		}
		else if (tmp->type == NAME && var_name_export(tmp->value) == ERROR)
		{
			error_export(tmp->value);
			tmp = tmp->next;
			(*j)++;
		}
		else
		{
			check_double_export(current->arg[*j], shell);
			tmp = tmp->next;
			(*j)++;
		}
	}
	return ;
}

int compare_with_env(t_shell *shell, t_token *tmp)
{
	int i;
	int j;

	i = 0;
	while (shell->env[i] != NULL)
	{
		j = 0;
		while (shell->env[i][j] != '=')
			j++;
		if (ft_strncmp(tmp->value, shell->env[i], j) == 0)
			//&& tmp->value[j] == '=' && shell->env[i][j] == '=')
		{

			return (VALID);
		}
		i++;
	}
	return(ERROR);
}
