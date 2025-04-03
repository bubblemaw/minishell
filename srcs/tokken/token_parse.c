/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/03 16:23:56 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	creat_list(t_shell *shell, char *input)
{
	shell->creat.content = ft_substr(input, shell->creat.begin, shell->creat.end - shell->creat.begin);
	shell->creat.new = creat_node(shell->creat.content);
	add_node(shell, shell->creat.new);
	return (0);
}

// void give_token_data(t_shell *shell)
// {
// 	shell->creat.end = shell->creat.i + 1;
// 	shell->tokken->type = REDIRECTION;
// 	return ;
// }

void	give_token_data(t_shell *shell)
{
	t_token	*temp;
	char	*first;

	temp = shell->tokken;
	first = ft_strdup(temp->value);
	if (first[0] == '<' || first[0] == '>')
	{
		temp->type = REDIRECTION;
		temp = temp->next;
		temp->type = ARGUMENT;
		temp = temp->next;
	}
	free(first);
	shell->creat.find = false;
	while (temp != NULL)
	{
		if (temp->value[0] == '>' 
			|| temp->value[0] == '<')
			temp->type = REDIRECTION;
		else if (temp->value[0] == '=')
		{
			temp->type = EQUALITY;
			temp->prev->type = NAME;
			temp->next->type = VALUE;
			temp = temp->next;
		}
		else if (temp->value[0] == '|')
		{
			temp->type = PIPE;
			shell->creat.find = false;
		}
		else if (temp->value[0] == '-' 
				&& temp->value[1] != ' ')
			temp->type = OPTION;
		else
		{
			if (shell->creat.find == true)
				temp->type = ARGUMENT;
			else
			{
				temp->type = COMMAND;
				shell->creat.find = true;
			}
		}
		temp = temp->next;
	}
	return ;
}
