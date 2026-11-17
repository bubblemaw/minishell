/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:36:45 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 11:41:10 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_kill_quotes(t_shell *shell)
{
	shell->kill.i = 0;
	shell->kill.start = 0;
	shell->kill.len = 0;
	shell->kill.new = NULL;
}

void	iterate_into_quote(t_shell *shell, t_token *temp, char c)
{
	shell->kill.i++;
	shell->kill.start = shell->kill.i;
	while (temp->value[shell->kill.i] != c
		&& temp->value[shell->kill.i] != '\0')
		shell->kill.i++;
	shell->kill.len = shell->kill.i - shell->kill.start;
	shell->kill.i++;
}

void	iterate_into_non_quote(t_shell *shell, t_token *temp)
{
	shell->kill.start = shell->kill.i;
	while (temp->value[shell->kill.i] != '\''
		&& temp->value[shell->kill.i] != '"'
		&& temp->value[shell->kill.i] != '\0')
		shell->kill.i++;
	shell->kill.len = shell->kill.i - shell->kill.start;
}
