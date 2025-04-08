/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/08 12:47:56 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int kill_quotes(t_shell *shell)
{
	int i;

	shell->kill.temp = shell->tokken;
	while (shell->kill.temp != NULL)
	{
		i = 0;
		while (shell->kill.temp->value[i] != '\0' && shell->kill.temp->type == ARGUMENT)
		{
			if (check_double_quotes(shell, shell->kill.temp->value + i, &i) != VALID)
				if (check_single_quotes(shell, shell->kill.temp->value + i, &i) != VALID)
					check_out_quotes(shell, shell->kill.temp->value + i, &i);
			creat_new_str(shell);
			if (shell->kill.temp->value[i] != '\0')
				i++;
		}
		if (shell->kill.new != NULL)
		{
			free(shell->kill.temp->value);
			shell->kill.temp->value = ft_strdup(shell->kill.new);
			free(shell->kill.new);
			shell->kill.new = NULL;
		}
		shell->kill.temp = shell->kill.temp->next;
	}
	return (0);
}

int	check_double_quotes(t_shell *shell, char *value, int *i)
{
	if (value[*i] == '"')
	{
		(*i)++;
		shell->kill.start = *i;
		while (value[*i] != '"' && value[*i] != '\0')
			(*i)++;
		shell->kill.len = *i - shell->kill.start;
		return (VALID);
	}
	return (0);
}

int	check_single_quotes(t_shell *shell, char *value, int *i)
{
	if (value[*i] == '\'')
	{
		(*i)++;
		shell->kill.start = *i;
		while (value[*i] != '\'' && value[*i] != '\0')
			(*i)++;
		shell->kill.len = *i - shell->kill.start;
		return (VALID);
	}
	return (0);
}

int	check_out_quotes(t_shell *shell, char *value, int *i)
{
	if (value[*i] != '"' && value[*i] != '\'')
	{
		shell->kill.start = *i;
		while (shell->kill.temp->value[*i] != '"'
				&& shell->kill.temp->value[*i] != '\''
				&& shell->kill.temp->value[*i] != '\0')
			(*i)++;
		shell->kill.len = *i - shell->kill.start;
		return (VALID);
	}
	return (0);
}

int	creat_new_str(t_shell *shell)
{
	if (shell->kill.len > 0)
	{
		if (shell->kill.new == NULL)
		shell->kill.new = ft_substr(shell->kill.temp->value, shell->kill.start, shell->kill.len);
		else
		{
			shell->kill.stash = ft_substr(shell->kill.temp->value, shell->kill.start, shell->kill.len);
			shell->kill.tmp = shell->kill.new;
			shell->kill.new = ft_strjoin(shell->kill.tmp, shell->kill.stash);
			free(shell->kill.stash);
			free(shell->kill.tmp);
			return (VALID);
		}	
	}
	return (0);
}

// int kill_quotes(t_shell *shell)
// {
// 	int		i;
// 	int 	start;
// 	int		len;
// 	t_token	*temp;
// 	char*	new;
// 	char*	tmp;
// 	char*	stash;

// 	i = 0;
// 	temp = shell->tokken;
// 	new = NULL;
// 	tmp = NULL;
// 	stash = NULL;
// 	while (temp != NULL)
// 	{
// 		i = 0;
// 		while (temp->value[i] != '\0' && temp->type == ARGUMENT)
// 		{
// 			if (temp->value[i] == '"')
// 			{
// 				i++;
// 				start = i;
// 				while (temp->value[i] != '"' && temp->value[i] != '\0')
// 					i++;
// 				len = i - start;
// 			}
// 			if (temp->value[i] == '\'')
// 			{
// 				i++;
// 				start = i;
// 				while (temp->value[i] != '\'' && temp->value[i] != '\0')
// 					i++;
// 				len = i - start;
// 			}
// 			if (temp->value[i] != '\'' && temp->value[i] != '"')
// 			{
// 				start = i;
// 				while (temp->value[i] != '"' && temp->value[i] != '\'' && temp->value[i] != '\0')
// 					i++;
// 				len = i - start;
// 			}
// 			if (len > 0)
// 			{
// 				if (new == NULL)
// 					new = ft_substr(temp->value, start, len);
// 				else
// 				{
// 					stash = ft_substr(temp->value, start, len);
// 					tmp = new;
// 					new = ft_strjoin(tmp, stash);
// 					free(stash);
// 					free(tmp);
// 				}	
// 			}
// 			if (temp->value[i] != '\0')
// 				i++;
// 		}
// 		if (new != NULL)
// 		{
// 			free(temp->value);
// 			temp->value = ft_strdup(new);
// 			free(new);
// 			new = NULL;
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }
