/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:45:09 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 12:54:30 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	put_new_var(t_shell *shell, char *tmp, int i, int j)
// {
// 	tmp = shell->exp.new;
// 	shell->exp.new = ft_strjoin(shell->exp.new, shell->env[i] + j);
// 	free(shell->exp.sub_env);
// 	free(tmp);
// 	return (0);
// }

int	inside(char *cur, int *i)
{
	if (cur[*i] == '\'')
	{
		(*i)++;
		while (cur[*i] != '\'' && cur[*i] != '\0')
			(*i)++;
		if (cur[*i] == '\'')
			(*i)++;
		return (VALID);
	}
	return (0);
}

void	inside_d(t_shell *shell, t_token *cur, int *i)
{
	if (cur->value[*i] == '"')
	{
		if (shell->exp.quot == false)
			shell->exp.quot = true;
		else
			shell->exp.quot = false;
	}
	return ;
}
