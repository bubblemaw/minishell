/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:56:21 by dchellen          #+#    #+#             */
/*   Updated: 2025/04/21 11:41:04 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	kill_quotes_new(t_shell *shell)
{
	t_token	*current;

	current = shell->tokken;
	init_kill_quotes(shell);
	while (current)
	{
		shell->kill.i = 0;
		iterate_into_token(shell, current);
		if (shell->kill.new != NULL)
			exchange_value(shell, current);
		current = current->next;
	}
	return (0);
}

void	iterate_into_token(t_shell *shell, t_token *current)
{
	while (current->value[shell->kill.i] != '\0' && (current->type == ARG
			|| current->type == COMMAND || current->type == OPTION))
	{
		if (current->value[shell->kill.i] == '"')
			iterate_into_quote(shell, current, '"');
		else if (current->value[shell->kill.i] == '\'')
			iterate_into_quote(shell, current, '\'');
		else if (current->value[shell->kill.i] != '\''
			&& current->value[shell->kill.i] != '"')
			iterate_into_non_quote(shell, current);
		if (shell->kill.len >= 0)
			create_new_value(shell, current);
	}
}

void	exchange_value(t_shell *shell, t_token *temp)
{
	free(temp->value);
	temp->value = ft_strdup(shell->kill.new);
	free(shell->kill.new);
	shell->kill.new = NULL;
}

void	create_new_value(t_shell *shell, t_token *temp)
{
	char	*stash;
	char	*tmp;

	tmp = NULL;
	stash = NULL;
	if (shell->kill.new == NULL)
		shell->kill.new = ft_substr(temp->value, shell->kill.start,
				shell->kill.len);
	else
	{
		stash = ft_substr(temp->value, shell->kill.start, shell->kill.len);
		tmp = shell->kill.new;
		shell->kill.new = ft_strjoin(tmp, stash);
		free(stash);
		free(tmp);
		tmp = NULL;
		stash = NULL;
	}
}
