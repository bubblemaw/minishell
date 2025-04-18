/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/17 10:22:25 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	init_kill_quotes(t_shell *shell)
// {
// 	shell->kill.i = 0;
// 	shell->kill.new = NULL;
// }

// int	kill_quotes_new(t_shell *shell)
// {
// 	t_token	*current;

// 	current = shell->tokken;
// 	while (current)
// 	{
// 		shell->kill.i = 0;
// 		while (current->value[shell->kill.i] != '\0' && (current->type == ARG
// 				|| current->type == COMMAND || current->type == OPTION))
// 		{
// 			if (current->value[shell->kill.i] == '"')
// 				iterate_into_quote(shell, current, '"');
// 			if (current->value[shell->kill.i] == '\'')
// 				iterate_into_quote(shell, current, '\'');
// 			if (current->value[shell->kill.i] != '\'' && current->value[shell->kill.i] != '\'')	
// 				iterate_into_non_quote(shell, current);
// 			if (shell->kill.len >= 0)
// 				create_new_value(shell, current);
// 			if (current->value[shell->kill.i] != '\0')
// 				shell->kill.i++;
// 		}
// 		if (shell->kill.new != NULL)
// 			exchange_value(shell, current);
// 		current = current->next;
// 	}
// 	return (0);
// }
// void exchange_value(t_shell *shell, t_token *temp)
// {
// 	free(temp->value);
// 	temp->value = ft_strdup(shell->kill.new);
// 	free(shell->kill.new);
// 	shell->kill.new = NULL;
// }
// void create_new_value(t_shell *shell, t_token *temp)
// {
// 	char *stash;
// 	char *tmp;

// 	tmp = NULL;
// 	stash = NULL;
// 	if (shell->kill.new == NULL)
// 		shell->kill.new = ft_substr(temp->value, shell->kill.start, shell->kill.len);
// 	else
// 	{
// 		stash = ft_substr(temp->value, shell->kill.start, shell->kill.len);
// 		tmp = shell->kill.new;
// 		shell->kill.new = ft_strjoin(tmp, stash);
// 		free(stash);
// 		free(tmp);
// 	}
// }


// void	iterate_into_quote(t_shell *shell, t_token *temp, char c)
// {
// 	shell->kill.i++;
// 	shell->kill.start = shell->kill.i;
// 	while (temp->value[shell->kill.i] != c && temp->value[shell->kill.i] != '\0')
// 		shell->kill.i++;
// 	shell->kill.len = shell->kill.i++ - shell->kill.start;
// }
// void	iterate_into_non_quote(t_shell *shell, t_token *temp)
// {
// 	shell->kill.i++;
// 	shell->kill.start = shell->kill.i;
// 	while (temp->value[shell->kill.i] != '\'' && temp->value[shell->kill.i] != '"'
// 		&& temp->value[shell->kill.i] != '\0')
// 		shell->kill.i++;
// 	shell->kill.len = shell->kill.i - shell->kill.start;
// }



int kill_quotes(t_shell *shell)
{
	int		i;
	int 	start;
	int		len;
	t_token	*temp;
	char*	new;
	char*	tmp;
	char*	stash;

	i = 0;
	temp = shell->tokken;
	new = NULL;
	tmp = NULL;
	stash = NULL;
	while (temp != NULL)
	{
		i = 0;
		while (temp->value[i] != '\0' && (temp->type == ARG
				|| temp->type == COMMAND || temp->type == OPTION))
		{
			if (temp->value[i] == '"')
			{
				i++;
				start = i;
				while (temp->value[i] != '"' && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			if (temp->value[i] == '\'')
			{
				i++;
				start = i;
				while (temp->value[i] != '\'' && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			if (temp->value[i] != '\'' && temp->value[i] != '"')
			{
				start = i;
				while (temp->value[i] != '"' && temp->value[i] != '\''
					 && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			if (len >= 0)
			{
				if (new == NULL)
					new = ft_substr(temp->value, start, len);
				else
				{
					stash = ft_substr(temp->value, start, len);
					tmp = new;
					new = ft_strjoin(tmp, stash);
					free(stash);
					free(tmp);
				}
			}
			if (temp->value[i] != '\0')
				i++;
		}
		if (new != NULL)
		{
			free(temp->value);
			temp->value = ft_strdup(new);
			free(new);
			new = NULL;
		}
		temp = temp->next;
	}
	return (0);
}

// int	kill_quotes(t_shell *sl)
// {
// 	int	i;

// 	sl->kill.temp = sl->tokken;
// 	while (sl->kill.temp != NULL)
// 	{
// 		i = 0;
// 		while (sl->kill.temp->value[i] != '\0'
// 			&& (sl->kill.temp->type == ARG || sl->kill.temp->type == OPTION || sl->kill.temp->type == COMMAND))
// 		{
// 			if (is_double(sl, sl->kill.temp->value + i, &i) != VALID)
// 				if (is_single(sl, sl->kill.temp->value + i, &i) != VALID)
// 					check_out_quotes(sl, sl->kill.temp->value + i, &i);
// 			creat_new_str(sl);
// 			if (sl->kill.temp->value[i] != '\0')
// 				i++;
// 		}
// 		if (sl->kill.new != NULL)
// 		{
// 			free(sl->kill.temp->value);
// 			sl->kill.temp->value = ft_strdup(sl->kill.new);
// 			free(sl->kill.new);
// 			sl->kill.new = NULL;
// 		}
// 		sl->kill.temp = sl->kill.temp->next;
// 	}
// 	return (0);
// }

// int	is_double(t_shell *shell, char *value, int *i)
// {
// 	if (value[*i] == '"')
// 	{
// 		(*i)++;
// 		shell->kill.start = *i;
// 		while (value[*i] != '"' && value[*i] != '\0')
// 			(*i)++;
// 		shell->kill.len = *i - shell->kill.start;
// 		return (VALID);
// 	}
// 	return (0);
// }

// int	is_single(t_shell *shell, char *value, int *i)
// {
// 	if (value[*i] == '\'')
// 	{
// 		(*i)++;
// 		shell->kill.start = *i;
// 		while (value[*i] != '\'' && value[*i] != '\0')
// 			(*i)++;
// 		shell->kill.len = *i - shell->kill.start;
// 		return (VALID);
// 	}
// 	return (0);
// }

// int	check_out_quotes(t_shell *shell, char *value, int *i)
// {
// 	if (value[*i] != '"' && value[*i] != '\'')
// 	{
// 		shell->kill.start = *i;
// 		while (shell->kill.temp->value[*i] != '"'
// 			&& shell->kill.temp->value[*i] != '\''
// 			&& shell->kill.temp->value[*i] != '\0')
// 			(*i)++;
// 		shell->kill.len = *i - shell->kill.start;
// 		return (VALID);
// 	}
// 	return (0);
// }

// int	creat_new_str(t_shell *shell)
// {
// 	if (shell->kill.len >= 0)
// 	{
// 		if (shell->kill.new == NULL)
// 			shell->kill.new = ft_substr(shell->kill.temp->value,
// 					shell->kill.start, shell->kill.len);
// 		else
// 		{
// 			shell->kill.stash = ft_substr(shell->kill.temp->value,
// 					shell->kill.start, shell->kill.len);
// 			shell->kill.tmp = shell->kill.new;
// 			shell->kill.new = ft_strjoin(shell->kill.tmp, shell->kill.stash);
// 			free(shell->kill.stash);
// 			free(shell->kill.tmp);
// 			return (VALID);
// 		}
// 	}
// 	return (0);
// }
