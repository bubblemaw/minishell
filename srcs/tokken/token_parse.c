/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/13 12:08:39 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	creat_list(t_shell *shell, char *input)
{
	shell->creat.content = ft_substr(input, shell->creat.begin,
			shell->creat.end - shell->creat.begin);
	shell->creat.new = creat_node(shell->creat.content);
	add_node(shell, shell->creat.new);
	return (0);
}

void	give_token_data(t_shell *shell)
{
	t_token	*temp;

	temp = shell->tokken;
	first_case(shell, &temp);
	shell->creat.find = false;
	while (temp != NULL)
	{
		give(&temp, &shell->creat.find);
		temp = temp->next;
	}
	return ;
}

void	first_case(t_shell *shell, t_token **temp)
{
	shell->creat.first = ft_strdup((*temp)->value);
	if (shell->creat.first[0] == '<' || shell->creat.first[0] == '>')
	{
		(*temp)->type = REDIRECTION;
		*temp = (*temp)->next;
		(*temp)->type = ARG;
		*temp = (*temp)->next;
	}
	free(shell->creat.first);
	return ;
}

void	give(t_token **temp, bool *find)
{
	if ((*temp)->value[0] == '>' || (*temp)->value[0] == '<')
		(*temp)->type = REDIRECTION;
	else if ((*temp)->value[0] == '=')
	{
		(*temp)->type = EQUALITY;
		(*temp)->prev->type = NAME;
		(*temp)->next->type = VALUE;
		*temp = (*temp)->next;
	}
	else if ((*temp)->value[0] == '|')
	{
		(*temp)->type = PIPE;
		*find = false;
	}
	else if ((*temp)->value[0] == '-'
		&& (*temp)->value[1] != ' ')
		(*temp)->type = OPTION;
	else if (*find == true)
		(*temp)->type = ARG;
	else
	{
		(*temp)->type = COMMAND;
		*find = true;
	}
	return ;
}
