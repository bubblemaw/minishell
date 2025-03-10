/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:52 by david             #+#    #+#             */
/*   Updated: 2025/03/10 12:08:47 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *str, int *i)
{
	int check_first;

	check_first = *i;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
	{
		if (str[*i] == '\0')
			return (0);
		(*i)++;
	}
	if (check_first == 0 &&
		(str[*i] == '=' || str[*i] == '|'))
		return (ERROR);
	return (0);
}

int	single_quotes(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	if (str[*i] != '\'')
		return (ERROR);
	return (VALID);
}

int	double_quotes(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '"' && str[*i] != '\0')
		(*i)++;
	if (str[*i] != '"')
		return (ERROR);
	return (VALID);
}

int	detect_redirections(char *str, int *i)
{
	int next;

	next = *i;
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (str[next + 1] == str[*i])
			(*i)++;
		if (str[next + 2] == '>' || str[next + 2] == '<' 
			|| (str[*i] == '>' && str[next + 1] == '<')
			|| (str[*i] == '<' && str[next + 1] == '>'))
			return (ERROR);
		return (VALID);
	}
	else if (str[*i] == '|')
	{
		if (str[next +1] == '|')
			return (ERROR);
		return (VALID);
	}
	return (0);
}

int detect_variables(bool *var, char *str, int *i)
{
	if (str[*i] == '=' && (str[*i + 1] == ' ' || str[*i - 1] == ' '))
		return (ERROR);
	else if (*i > 0 && str[*i - 1] == '=' && *var == true)
	{
		while (str[*i] != ' ' && str[*i] != '\0'
				&& str[*i] != '>' && str[*i] != '<'
				&& str[*i] != '|')
		{
			if (detect_var_value(str, i) == ERROR)
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
	int result;

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
	int result;

	result = 0;
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '=' && input[*i] != '\0')
	{
		if (input[*i] == '"')
			result = double_quotes(input, i);
		else if (input[*i] == '\'')
			result = single_quotes(input, i);
		if (result == ERROR)
			return (ERROR);
		(*i)++;
	}
	return (VALID);
}
