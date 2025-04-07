/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/07 11:26:44 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int kill_quotes(t_shell *shell)
{
	t_token *temp;
	int		i;
	int		start;
	int		len;
	char	*new;
	char	*tmp;
	char	*stash;

	temp = shell->tokken;
	i = 0;
	start = 0;
	len = 0;
	new = NULL;
	tmp = NULL;
	stash = NULL;
	while (temp != NULL)
	{
		i = 0;
		while (temp->value[i] != '\0' && temp->type == ARGUMENT)
		{
			if (temp->value[i] == '"')
			{
				i++;
				start = i;
				while (temp->value[i] != '"' && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			else if (temp->value[i] == '\'')
			{
				i++;
				start = i;
				while (temp->value[i] != '\'' && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			else
			{
				start = i;
				while (temp->value[i] != '"' && temp->value[i] != '\'' && temp->value[i] != '\0')
					i++;
				len = i - start;
			}
			if (len > 0)
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
		}
		temp = temp->next;
	}
	return (0);
}
