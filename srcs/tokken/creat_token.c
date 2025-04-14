/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/14 14:51:37 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	enter_input(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->input[0] == '\0')
		return (VALID);
	while ((shell->input[i] >= 9 && shell->input[i] <= 13)
		|| shell->input[i] == 32)
		i++;
	if (shell->input[i] == '\0')
		return (VALID);
	return (0);
}

int	creat_tokken(char *input, t_shell *shell)
{
	shell->creat.i = 0;
	while (input[shell->creat.i] != '\0')
	{
		if (skip_space(input, &shell->creat.i) == ERROR)
			return (ERROR);
		if (input[shell->creat.i] == '\0')
			break ;
		if (parsing(input, shell) == ERROR)
			return (ERROR);
	}
	if (shell->creat.content != NULL
		&& (shell->creat.content[0] == '<' || shell->creat.content[0] == '>'
			|| shell->creat.content[0] == '|'))
		return (ERROR);
	return (0);
}

int	parsing(char *input, t_shell *shell)
{
	shell->creat.begin = shell->creat.i;
	shell->creat.v_res = detect_variables(&shell->creat.var,
			input, &shell->creat.i);
	if (shell->creat.v_res == ERROR)
		return (ERROR);
	else if (shell->creat.v_res == VALID)
		shell->creat.end = shell->creat.i;
	else if (detect_redirections(input, &shell->creat.i) == ERROR)
		return (ERROR);
	else if (detect_redirections(input, &shell->creat.i) == VALID)
	{
		shell->creat.end = shell->creat.i + 1;
		shell->creat.i++;
	}
	else if (detect_command(input, &shell->creat.i) == ERROR)
		return (ERROR);
	else
		shell->creat.end = shell->creat.i;
	if (shell->creat.begin < shell->creat.end)
		creat_list(shell, input);
	return (0);
}
