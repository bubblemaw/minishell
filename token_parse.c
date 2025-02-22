/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:52 by david             #+#    #+#             */
/*   Updated: 2025/02/22 14:39:59 by david            ###   ########.fr       */
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

int	double_quotes(char *str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
		if (str[*i] == '"')
		{
			(*i)++;
			return (VALID);
		}
	}
	return (0);
}

int	single_quotes(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
		if (str[*i] == '\'')
		{
			(*i)++;
			return (VALID);
		}
	}
	return (0);
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
	else if (str[*i] == '|' || str[*i] == '=')
	{
		if (str[next +1] == '|')
			return (ERROR);
		else if (str[*i] == '=' && 
			(str[*i + 1] == ' ' || str[*i - 1] == ' '
			|| str[*i + 1] == '=' || str[*i - 1] == '='))
			return (ERROR);
		return (VALID);
	}
	return (0);
}

int	detect_command(char *input, int *i)
{
	while (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '=' && input[*i] != '\0')
		(*i)++;
	if (input[*i] != ' ' && input[*i] != '>'
		&& input[*i] != '<' && input[*i] != '|'
		&& input[*i] != '=' && input[*i] != '\0')
		return (ERROR);
	return (VALID);
}
