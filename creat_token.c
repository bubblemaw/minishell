/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/24 20:44:13 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_tokken(char *input, t_shell *shell)
{
	shell->creat.i = 0;
	while (input[shell->creat.i] != '\0')
	{
		// debut
		if (skip_space(input, &shell->creat.i) == ERROR)
			return (ERROR);
		if (input[shell->creat.i] == '\0')
			break ;
		shell->creat.begin = shell->creat.i;

		// gestion des doubles quotes
		if ((double_quotes(input, &shell->creat.i)) == ERROR)
			return (ERROR);
		else if (double_quotes(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;

		// gestion des single quotes
		if (single_quotes(input, &shell->creat.i) == ERROR)
			return (ERROR);
		else if (single_quotes(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;

		// gestion des redirections
		else if (detect_redirections(input, &shell->creat.i) == ERROR)
			return (ERROR);
		else if (detect_redirections(input, &shell->creat.i) == VALID)
		{
			shell->creat.end = shell->creat.i + 1;
			shell->creat.i++;
		}

		// gestion de la commande
		else if (detect_command(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;
		// else if (detect_command(input, &shell->creat.i) == ERROR)
		// 	return (ERROR);

		//creation de la liste
		shell->creat.content = ft_substr(input, shell->creat.begin, shell->creat.end - shell->creat.begin);
		shell->creat.new = creat_node(shell->creat.content);
		add_node(shell, shell->creat.new);
	}
	shell->creat.last_token = shell->creat.content;
	if (shell->creat.last_token[0] == '<' || shell->creat.last_token[0] == '>'
		|| shell->creat.last_token[0] == '|')
		return (ERROR);
	printf("\n");
	print_token(shell->tokken);
	printf("\n");
	return (0);
}
