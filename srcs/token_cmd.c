/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:01 by maw               #+#    #+#             */
/*   Updated: 2025/03/03 19:58:22 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int creat_cmd_lst(t_shell *shell, t_tok *tok)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	while (tok)
	{
		if (tok->type == REDIRECTION)
			ft_cmd_redirection(shell, tok, cmd);
		if (tok->type == CMD)
			ft_cmd_maker(shell, tok, cmd);
		if (tok->type == PIPE)
		{
			ft_cmd_pipe();
			tok = tok->next;
		}
	}
	free(tok);
	return (1);
}

int ft_cmd_redirection(t_shell *shell, t_tok *tok, t_cmd *cmd)
{
	if (tok->str == '>')
	{
		tok = tok->next;
		cmd->outfile = ft_strdup(tok->str);
	}	
	if (tok->str == '<')
	{
		tok = tok->next;
		cmd->infile = ft_strdup(tok->str);
	}	
	if (tok->str == '>>')
	{
		tok = tok->next;
		cmd->outfile = ft_strdup(tok->str);
		cmd->append = 1;
	}	
	if (tok->str == '<<')
	{
		tok = tok->next;
		cmd->delimiter = ft_strdup(tok->str);
	}
	tok = tok->next;
	return (1);
}

int ft_cmd_maker(t_shell *shell, t_tok *tok, t_cmd *cmd)
{
	int i;

	i = 0;
	while(tok && tok->type == ARG || tok->type == OPTION)
	{
		cmd->arg[i] = ft_strdup(tok->str);
		tok = tok->next;
		i++;
		cmd->arg = ft_realloc(cmd->arg, i + 1);
	}
	cmd->arg = ft_realloc(cmd->arg, i + 1);
	cmd->arg[i] = NULL;
	return (1);
}
