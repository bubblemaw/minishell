/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/03 23:25:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int creat_list(t_shell *shell, char *input)
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

void give_token_data(t_shell *shell)
{
	t_token *temp;

	temp = shell->tokken;
	while (temp != NULL)
	{
		if (temp->value[0] == '\'')
			temp->type = 1;
		else if (temp->value[0] == '"')
			temp->type = 2;
		else if (temp->value[0] == '>' 
				|| temp->value[0] == '<')
			temp->type = 3;
		else if (temp->value[0] == '=')
			temp->type = 4;
		else if (temp->value[0] == '|')
			temp->type = 5;
		else
			temp->type = 0;
		temp = temp->next;
	}
	return ;
}
