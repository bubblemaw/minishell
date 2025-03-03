/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/03 17:20:51 by dchellen         ###   ########.fr       */
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
	while (shell->tokken != NULL)
	{
		if (shell->tokken->value[0] == '\'')
			shell->tokken->type = 1;
		else if (shell->tokken->value[0] == '"')
			shell->tokken->type = 2;
		else if (shell->tokken->value[0] == '>' 
				|| shell->tokken->value[0] == '<')
			shell->tokken->type = 3;
		else if (shell->tokken->value[0] == '=')
			shell->tokken->type = 4;
		else if (shell->tokken->value[0] == '|')
			shell->tokken->type = 5;
		else
			shell->tokken->type = 0;
		shell->tokken = shell->tokken->next;
	}
	return ;
}
