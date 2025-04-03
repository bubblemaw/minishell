/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/03 16:16:22 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	enter_input(t_shell *shell)
{
	if (shell->input[0] == '\0')
	{
		free(shell->input);
		return (VALID);
	}
	return (0);
}

int	creat_tokken(char *input, t_shell *shell)
{
	int	var_result;

	shell->creat.i = 0;
	while (input[shell->creat.i] != '\0')
	{
		// debut
		if (skip_space(input, &shell->creat.i) == ERROR)
			return (ERROR);
		if (input[shell->creat.i] == '\0')
			break ;
		shell->creat.begin = shell->creat.i;

		// gestion des variables
		var_result = detect_variables(&shell->creat.var, input, &shell->creat.i);
		if (var_result == ERROR)
			return (ERROR);
		else if (var_result == VALID)
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
		else if (detect_command(input, &shell->creat.i) == ERROR)
			return (ERROR);
		else
			shell->creat.end = shell->creat.i;
		if (shell->creat.begin < shell->creat.end)
			creat_list(shell, input);
		if (shell->creat.content)
		{
			printf("on free le content \n");
			if (input[shell->creat.i + 1] != '\0')
				free(shell->creat.content);
		}
	}
	shell->creat.last_token = shell->creat.content;
	if (shell->creat.last_token[0] == '<' || shell->creat.last_token[0] == '>'
		|| shell->creat.last_token[0] == '|')
	{
		free(shell->creat.last_token);
		return (ERROR);
	}
	if (shell->creat.content)
	{
		printf("on free le last \n");
		free(shell->creat.last_token);
	}
	
	return (0);
}
