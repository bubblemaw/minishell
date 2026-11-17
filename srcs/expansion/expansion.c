/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/04/21 12:44:34 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_expansion(t_shell *shell)
{
	t_token	*current;
	t_var	*temp;

	current = shell->tokken;
	temp = shell->var;
	while (current != NULL)
	{
		if (current->type == ARG || current->type == COMMAND)
			find_var(shell, current, temp);
		current = current->next;
	}
	return (VALID);
}

int	find_var(t_shell *shell, t_token *cur, t_var *temp)
{
	int		i;

	i = 0;
	while (cur->value[i] != '\0')
	{
		if (inside(cur->value, &i) == VALID)
			continue ;
		inside_d(shell, cur, &i);
		if (cur->value[i] == '$' || (cur->value[i] == '~' && i - 1 < 0
				&& (cur->value[i + 1] == ' ' || cur->value[i + 1] == '/'
					|| cur->value[i + 1] == '\0')))
		{
			new_arg(shell, cur->value, &i);
			if (special_cases(shell, cur->value + i, &i) == VALID)
				continue ;
			search_var(shell, cur, &i, temp);
			shell->exp.start = i;
		}
		else
			i++;
	}
	result(shell, cur, &i);
	shell->exp.size_var = 0;
	shell->exp.quot = false;
	return (0);
}

int	search_var(t_shell *shell, t_token *cur, int *i, t_var *temp)
{
	int		var_found;

	only_dolls(shell, cur->value + *i);
	var_found = 0;
	if (search_local_var(shell, cur->value + *i, temp) == VALID)
		var_found = 1;
	else if (search_export_var(shell, cur->value + *i) == VALID)
		var_found = 1;
	if (var_found)
		*i += shell->exp.size_var + 1;
	else
	{
		*i += shell->exp.size_var + 1;
		shell->exp.size_var = 0;
	}
	return (0);
}

int	new_arg(t_shell *shell, char *value, int *i)
{
	if (shell->exp.new == NULL)
		shell->exp.new = ft_substr(value, 0, *i);
	else
	{
		shell->exp.add = ft_substr(value,
				shell->exp.start, *i - shell->exp.start);
		shell->exp.tmp = shell->exp.new;
		shell->exp.new = ft_strjoin(shell->exp.new, shell->exp.add);
		free(shell->exp.tmp);
		free(shell->exp.add);
	}
	return (0);
}

int	var_size(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$' && str[1] != '\0')
		str++;
	while (str[i] != ' ' && str[i] != '\0'
		&& str[i] != '$' && str[i] != '"'
		&& str[i] != '\'')
		i++;
	return (i);
}
