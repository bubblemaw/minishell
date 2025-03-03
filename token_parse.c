/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:17:05 by dchellen          #+#    #+#             */
/*   Updated: 2025/03/02 16:22:31 by david            ###   ########.fr       */
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
		shell->tokken = shell->tokken->next;
	}
	return ;
}
