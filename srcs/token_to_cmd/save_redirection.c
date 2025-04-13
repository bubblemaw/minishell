/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:36:45 by masase            #+#    #+#             */
/*   Updated: 2025/04/13 20:28:55 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_outfile(t_shell *shell, t_cmd *cmd)
{
	shell->redir.prev_outfile = ft_strdup(cmd->outfile);
	shell->redir.apppend = cmd->append;
	shell->redir.type = cmd->type;
	free(cmd->outfile);
	cmd->outfile = NULL;
	cmd->append = 0;
	new_cmd_redirection(&shell->cmd, shell);
}

void	save_infile(t_shell *shell, t_cmd *cmd)
{
	shell->redir.prev_infile = ft_strdup(cmd->infile);
	free(cmd->infile);
	cmd->infile = NULL;
	new_cmd_redirection(&shell->cmd, shell);
}

void	save_delimiter(t_shell *shell, t_cmd *cmd)
{
	shell->redir.prev_delimiter = ft_strdup(cmd->delimiter);
	free(cmd->delimiter);
	cmd->delimiter = NULL;
	shell->redir.type = cmd->type;
	new_cmd_redirection(&shell->cmd, shell);
}
