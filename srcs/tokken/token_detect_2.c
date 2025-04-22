/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detect_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:03:24 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/22 22:57:49 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	detect_redirections(char *str, int *i)
{
	int	next;

	next = *i;
	if ((str[*i] == '>' || str[*i] == '<'))
	{
		if (str[next + 1] != '\0' && str[next + 1] == str[*i])
			(*i)++;
		if (str[next + 1] != '\0' && str[next + 2] != '\0'
			&& (str[next + 2] == '>' || str[next + 2] == '<'
				|| (str[*i] == '>' && str[next + 1] == '<')
				|| (str[*i] == '<' && str[next + 1] == '>')))
			return (ERROR);
		return (VALID);
	}
	else if (str[*i] == '|')
	{
		if (str[next + 1] != '\0' && str[next +1] == '|')
			return (ERROR);
		return (VALID);
	}
	return (0);
}

int	detect_variables(bool *var, char *str, int *i)
{
	if (str[*i] == '=' && (str[*i + 1] == ' ' || str[*i + 1] == '\0'
			|| str[*i - 1] == ' '))
		return (ERROR);
	else if (*i > 0 && str[*i - 1] == '=' && *var == true)
	{
		while (str[*i] != ' ' && str[*i] != '\0'
			&& str[*i] != '>' && str[*i] != '<'
			&& str[*i] != '|')
		{
			if (detect_var_value(str, i) == ERROR)
				return (ERROR);
			else if (str[*i] == '\\' || str[*i] == ';')
				return (ERROR);
			(*i)++;
		}
		*var = false;
		return (VALID);
	}
	else if (str[*i] == '=')
	{
		(*i)++;
		*var = true;
		return (VALID);
	}
	return (0);
}

int	detect_var_value(char *input, int *i)
{
	int	result;

	result = 0;
	if (input[*i] == '"')
		result = double_quotes(input, i);
	else if (input[*i] == '\'')
		result = single_quotes(input, i);
	if (result == ERROR)
		return (ERROR);
	return (VALID);
}

int	detect_command(char *input, int *i)
{
	int	result;

	result = 0;
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '=' && input[*i] != '\0')
	{
		if (input[*i] == '"')
			result = double_quotes(input, i);
		else if (input[*i] == '\'')
			result = single_quotes(input, i);
		if (result == ERROR || input[*i] == '\\' || input[*i] == ';')
			return (ERROR);
		(*i)++;
	}
	return (VALID);
}
