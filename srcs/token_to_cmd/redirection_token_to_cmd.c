/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_token_to_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:32:11 by masase            #+#    #+#             */
/*   Updated: 2025/04/20 12:13:34 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cmd_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell)
{
	if (ft_strlen((*tokken)->value) > 1)
		double_redirection(cmd, tokken, shell);
	else
		simple_redirection(cmd, tokken, shell);
	*tokken = (*tokken)->next;
	return (VALID);
}

void	double_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell)
{
	if ((*tokken)->value[0] == '>' && (*tokken)->value[1] == '>')
	{
		*tokken = (*tokken)->next;
		if (cmd->outfile)
		{
			save_outfile(shell, cmd);
		}
		cmd->outfile = ft_strdup((*tokken)->value);
		cmd->append = 1;
	}
	else if ((*tokken)->value[0] == '<' && (*tokken)->value[1] == '<')
	{
		*tokken = (*tokken)->next;
		if (cmd->infile)
			save_infile(shell, cmd);
		else if (cmd->delimiter)
			save_delimiter(shell, cmd);
		cmd->delimiter = ft_strdup((*tokken)->value);
		cmd->type = DELIMITER;
	}
}

void	simple_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell)
{
	if ((*tokken)->value[0] == '>')
	{
		*tokken = (*tokken)->next;
		if (cmd->outfile)
			save_outfile(shell, cmd);
		cmd->outfile = ft_strdup((*tokken)->value);
	}
	else if ((*tokken)->value[0] == '<')
	{
		*tokken = (*tokken)->next;
		if (cmd->infile)
			save_infile(shell, cmd);
		else if (cmd->delimiter)
			save_delimiter(shell, cmd);
		cmd->infile = ft_strdup((*tokken)->value);
	}
}

int	new_cmd_redirection(t_cmd **head_cmd, t_shell *shell)
{
	t_cmd	*current;

	add_cmd_before_last(head_cmd);
	current = *head_cmd;
	while (current->next->next)
		current = current->next;
	setup_cmd_lst(&current);
	if (shell->redir.prev_infile)
		current->infile = ft_strdup(shell->redir.prev_infile);
	if (shell->redir.prev_outfile)
		current->outfile = ft_strdup(shell->redir.prev_outfile);
	if (shell->redir.prev_delimiter)
		current->delimiter = ft_strdup(shell->redir.prev_delimiter);
	current->append = shell->redir.apppend;
	current->type = shell->redir.type;
	free_new_redirection(shell);
	return (VALID);
}
