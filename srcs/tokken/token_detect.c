/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:52 by david             #+#    #+#             */
/*   Updated: 2025/04/14 12:04:50 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_space(char *str, int *i)
{
	int	check_first;

	check_first = *i;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
	{
		if (str[*i] == '\0')
			return (0);
		(*i)++;
	}
	if (check_first == 0
		&& (str[*i] == '=' || str[*i] == '|'))
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
