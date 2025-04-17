/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:06:09 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/17 14:25:20 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	make_export(t_shell *shell, t_cmd *current, t_token *tmp, int *j)
{
	while (current->arg[*j] != NULL)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
		{
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
