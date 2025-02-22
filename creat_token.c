/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:02:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/02/22 14:46:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_tokken(char *input, t_shell *shell)
{
	while (input[shell->creat.i] != '\0')
	{
		if (skip_space(input, &shell->creat.i) == ERROR)
			return (ERROR);
		if (input[shell->creat.i] == '\0')
			break ;
		shell->creat.begin = shell->creat.i;
		if (double_quotes(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;
		else if (single_quotes(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;
		else if (detect_redirections(input, &shell->creat.i) == ERROR)
			return (ERROR);
		else if (detect_redirections(input, &shell->creat.i) == VALID)
		{
			shell->creat.end = shell->creat.i + 1;
			shell->creat.i++;
		}
		else if (detect_command(input, &shell->creat.i) == VALID)
			shell->creat.end = shell->creat.i;
		else if (detect_command(input, &shell->creat.i) == ERROR)
			return (ERROR);
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
