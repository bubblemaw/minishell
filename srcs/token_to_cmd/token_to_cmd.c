/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:01 by maw               #+#    #+#             */
/*   Updated: 2025/03/17 17:35:14 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int new_cmd(t_cmd **head_cmd, t_cmd **current)
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

int free_new_direction(t_shell *shell)
{
	if (shell->redir.prev_infile)
		free(shell->redir.prev_infile);
	if (shell->redir.prev_outfile)
		free(shell->redir.prev_outfile);
	if (shell->redir.prev_delimiter)
		free(shell->redir.prev_delimiter);
	shell->redir.prev_infile = NULL;
	shell->redir.prev_outfile = NULL;
	shell->redir.prev_delimiter = NULL;
	shell->redir.apppend = 0;
	shell->redir.type = 0;
	return (VALID);
}

int new_cmd_direction(t_cmd **head_cmd, t_shell *shell)
{
	t_cmd *current;
	
	add_cmd_lst(head_cmd);
	current = *head_cmd;
	if (!head_cmd)
		return (ERROR);
	while ((current)->next)
		current = (current)->next;
	setup_cmd_lst(&current);
	if (shell->redir.prev_infile)
		current->infile = ft_strdup(shell->redir.prev_infile);
	if (shell->redir.prev_outfile)
		current->outfile = ft_strdup(shell->redir.prev_outfile);
	if (shell->redir.prev_delimiter)
		current->delimiter = ft_strdup(shell->redir.prev_delimiter);
	current->append = shell->redir.apppend;
	current->type = shell->redir.type;
	free_new_direction(shell);
	return (VALID);
}

int create_cmd_lst(t_shell *shell)
{
	t_cmd *current;
	t_token *tokken;

	current = shell->cmd;
	tokken = shell->tokken;
	new_cmd(&shell->cmd, &current);
	while (tokken)
	{
		if (tokken->type == COMMAND)
			ft_cmd_maker(current, &tokken);
		else if (tokken->type == PIPE)
		{
			ft_cmd_pipe(current, &tokken);
			new_cmd(&shell->cmd, &current);
		}
		else if (tokken->type == REDIRECTION)
		{
			ft_cmd_redirection(current, &tokken, shell);
		}
		else if (tokken && tokken->type == ARGUMENT)
			ft_cmd_maker(current, &tokken);
		print_cmds(shell->cmd);
		printf("yooooooooooooooooooooooooo\n");
	}
	return (VALID);
}

int		save_redirection(t_shell *shell, t_cmd *cmd)
{
	if (cmd->infile)
	{
		shell->redir.prev_infile = ft_strdup(cmd->infile);
		free (cmd->infile);
	}
	if (cmd->outfile)
	{
		shell->redir.prev_outfile = ft_strdup(cmd->outfile);
		shell->redir.apppend = cmd->append;
		cmd->append = 0;
		free(cmd->outfile);
	}
	if (cmd->delimiter)
	{
		shell->redir.prev_delimiter = ft_strdup(cmd->delimiter);
		shell->redir.type = cmd->type;
		cmd->type = 0;
		free (cmd->delimiter);
	}
	return (VALID);
}

int ft_cmd_redirection(t_cmd *cmd, t_token **tokken, t_shell *shell)
{
	if (ft_strlen((*tokken)->value) > 1)
	{
		if (cmd->infile || cmd->delimiter || cmd->outfile)
		{
			save_redirection(shell, cmd);
			new_cmd_direction(&cmd, shell);
		}
		double_redirection(cmd, tokken);
	}
	else
	{
		if (cmd->infile || cmd->outfile)
		{
			save_redirection(shell, cmd);
			new_cmd_direction(&cmd, shell);
		}	
		simple_redirection(cmd, tokken);
	}	
	*tokken = (*tokken)->next;
	return (VALID);
}

void double_redirection(t_cmd *cmd, t_token **tokken)
{
	if ((*tokken)->value[0] == '>' && (*tokken)->value[1] == '>')
	{
		*tokken = (*tokken)->next;
		cmd->outfile = ft_strdup((*tokken)->value);
		cmd->append = 1;
	}	
	if ((*tokken)->value[0] == '<' && (*tokken)->value[1] == '<')
	{
		*tokken = (*tokken)->next;
		cmd->delimiter = ft_strdup((*tokken)->value);
		cmd->type = DELIMITER;
	}
}

void simple_redirection(t_cmd *cmd, t_token **tokken)
{
	if ((*tokken)->value[0] == '>')
	{
		*tokken = (*tokken)->next;
		cmd->outfile = ft_strdup((*tokken)->value);
	}	
	else if ((*tokken)->value[0] == '<')
	{
		*tokken = (*tokken)->next;
		cmd->infile = ft_strdup((*tokken)->value);
	}	
}

int ft_cmd_maker(t_cmd *cmd, t_token **tokken)
{
	int i;

	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i] != NULL)
			i++;
	}
	while (*tokken && ((*tokken)->type == OPTION || (*tokken)->type == ARGUMENT || (*tokken)->type == COMMAND))
	{
		cmd->arg = ft_realloc(cmd->arg, i * sizeof(char *), (i + 1) * sizeof(char *));
		cmd->arg[i] = ft_strdup((*tokken)->value);
		if (cmd->arg[i] == NULL)
			return (ERROR);
		i++;
		*tokken = (*tokken)->next;
	}
	cmd->arg = ft_realloc(cmd->arg, i * sizeof(char *), (i + 1) * sizeof(char *));
	cmd->arg[i] = NULL;
	return (VALID);
}
int ft_cmd_pipe(t_cmd *cmd, t_token **tokken)
{
	*tokken = (*tokken)->next;
	cmd->type = PIPE;
	return (VALID);
}
t_cmd *end_list(t_cmd *head)
{
	while((head)->next)
		head = (head)->next;
	return (head);
}

