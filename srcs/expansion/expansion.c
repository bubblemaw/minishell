/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:31:47 by maw               #+#    #+#             */
/*   Updated: 2025/04/09 14:34:15 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_expansion(t_shell *shell)
{
	t_token	*current;

	current = shell->tokken;
	while (current != NULL)
	{
		if (is_double_quote(current) == VALID && current->type == ARG)
			find_var(shell, current);
		current = current->next;
	}
	return (VALID);
}

int	is_double_quote(t_token *tokken)
{
	int	last_char;

	last_char = ft_strlen(tokken->value) - 1;
	if (ft_strlen(tokken->value) == 1 && tokken->value[0] == '$')
		return (0);
	else if (tokken->value[0] == '"' && tokken->value[last_char] == '"')
		return (VALID);
	else if (ft_strlen(tokken->value) >= 1 && tokken->value[0] != '\'')
		return (VALID);
	return (0);
}

int	find_var(t_shell *shell, t_token *current)
{
	t_var	*temp;
	int		i;

	temp = shell->var;
	i = 0;
	while (current->value[i] != '\0')
	{
		if (current->value[i] == '$'
			|| (current->value[i] == '~' && i - 1 < 0
			&& (current->value[i + 1] == ' ' || current->value[i + 1] == '/'
			|| current->value[i + 1] == '\0')))
		{
			printf("ENTER\n");
			new_arg(shell, current->value, &i);
			if (error_case(shell, current->value + i, &i) == VALID)
				continue ;
			if (pid_dolls(shell, current->value + i, &i) == VALID)
				continue ;
			if (wave(shell, current->value + i, &i) == VALID)
				continue ;
			only_dolls(shell, current, &i);
			if (search_local_var(shell, current->value + i, temp) != VALID)
				search_export_var(shell, current->value + i);
			i += shell->exp.size_var + 1;
			shell->exp.start = i;
		}
		else
			i++;
	}
	result(shell, current, &i);
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
