/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:01 by maw               #+#    #+#             */
/*   Updated: 2025/04/20 12:13:51 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_cmd_lst(t_shell *shell)
{
	t_cmd	*current;
	t_token	*tokken;

	current = shell->cmd;
	tokken = shell->tokken;
	new_cmd(&shell->cmd, &current);
	while (tokken)
	{
		if (tokken->type == NAME || tokken->type == EQUALITY
			|| tokken->type == VALUE)
			tokken = tokken->next;
		else if (tokken->type == COMMAND)
			ft_cmd_maker(shell, current, &tokken);
		else if (tokken->type == PIPE)
		{
			ft_cmd_pipe(current, &tokken);
			new_cmd(&shell->cmd, &current);
		}
		else if (tokken->type == REDIRECTION)
			ft_cmd_redirection(current, &tokken, shell);
		else if ((tokken && tokken->type == ARG) || tokken->type == OPTION)
			ft_cmd_maker(shell, current, &tokken);
	}
	return (VALID);
}

int	ft_cmd_maker(t_shell *shell, t_cmd *cmd, t_token **tokken)
{
	int	i;

	i = last_arg(cmd);
	shell->exp.valid = 0;
	if (ft_strlen((*tokken)->value) == 6
		&& ft_strncmp((*tokken)->value, "export", 6) == 0)
		shell->exp.valid = 1;
	while (*tokken && ((*tokken)->type == OPTION || (*tokken)->type == ARG
			|| (*tokken)->type == COMMAND || (*tokken)->type == NAME
			|| (*tokken)->type == EQUALITY || (*tokken)->type == VALUE))
	{
		if ((*tokken)->type == NAME && shell->exp.valid == 1)
			join_var(tokken);
		cmd->arg = ft_realloc(cmd->arg, i * sizeof(char *),
				(i + 1) * sizeof(char *));
		cmd->arg[i] = ft_strdup((*tokken)->value);
		if (cmd->arg[i] == NULL)
			return (ERROR);
		i++;
		*tokken = (*tokken)->next;
	}
	cmd->arg = ft_realloc(cmd->arg, i * sizeof(char *),
			(i + 1) * sizeof(char *));
	cmd->arg[i] = NULL;
	return (VALID);
}

int	last_arg(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i] != NULL)
			i++;
	}
	return (i);
}

int	new_cmd(t_cmd **head_cmd, t_cmd **current)
{
	add_cmd_lst(head_cmd);
	*current = *head_cmd;
	if (!head_cmd)
		return (ERROR);
	while ((*current)->next)
		*current = (*current)->next;
	setup_cmd_lst(current);
	return (VALID);
}

int	ft_cmd_pipe(t_cmd *cmd, t_token **tokken)
{
	*tokken = (*tokken)->next;
	cmd->type = PIPE;
	return (VALID);
}
