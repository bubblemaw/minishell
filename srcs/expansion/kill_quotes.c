/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/20 14:38:22 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int kill_quotes(t_shell *shell)
{
	t_token	*temp;
	char	*stash;
	char	*new;
	char	*tmp;
	int		i;

	temp = shell->tokken;
	new = NULL;
	while (temp != NULL)
	{
		i = 0;
		while (temp->value[i] != '\0')
		{
			if (temp->value[i] != '"' && temp->value[i] != '\'')
			{
				shell->creat.start = i;
				while (temp->value[i] != '"' && temp->value[i] != '\''
					   && temp->value[i] != '\0')
					i++;
				shell->creat.len = i - shell->creat.start;
				stash = ft_substr(temp->value, shell->creat.start, shell->creat.len);
				if (new == NULL)
				{
					new = ft_strdup(stash);
					if (new == NULL)
						return (0);
				}
				else
				{
					tmp = ft_strjoin(new, stash);
					free(new);
					new = tmp;
				}
			}
			if (temp->value[i] == '"' || temp->value[i] == '\'')
			{
				size_to_kill(temp, shell, &i);
				stash = ft_substr(temp->value, shell->creat.start, shell->creat.len);
				if (new == NULL)
				{
					new = ft_strdup(stash);
					if (new == NULL)
						return (0);
				}
				else
				{
					tmp = ft_strjoin(new, stash);
					free(new);
					new = tmp;
				}
			}
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

void size_to_kill(t_token *token, t_shell *shell, int *i)
{
	if (token->value[*i] == '\'')
	{
		(*i)++;
		shell->creat.start = *i;
		while (token->value[*i] != '\'' && token->value[*i] != '\0')
			(*i)++;
		shell->creat.len = *i - shell->creat.start;
	}
	else if (token->value[*i] == '"')
	{
		(*i)++;
		shell->creat.start = *i;
		while (token->value[*i] != '"' && token->value[*i] != '\0')
			(*i)++;
		shell->creat.len = *i - shell->creat.start;
	}
	return ;
}
