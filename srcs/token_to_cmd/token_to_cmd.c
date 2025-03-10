/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:01 by maw               #+#    #+#             */
/*   Updated: 2025/03/10 15:52:23 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int create_cmd_lst(t_shell *shell)
{
	t_cmd *current;
	t_token *tokken;

	add_cmd_lst(&shell->cmd);
	if (!shell->cmd)
		return (ERROR);
	setup_cmd_lst(shell->cmd);
	current = shell->cmd;
	tokken = shell->tokken;
	while (tokken)
	{
		if (tokken->type == REDIRECTION)
			ft_cmd_redirection(current, &tokken);
		else if (tokken->type == COMMAND)
			ft_cmd_maker(current, &tokken);
		else if (tokken->type == PIPE)
		{
			ft_cmd_pipe(current);
			tokken = tokken->next;
			add_cmd_lst(&shell->cmd);
			if (!shell->cmd)
				return (ERROR);
			current = end_list(shell->cmd);
			setup_cmd_lst(current);
		}
	}
	return (VALID);
}

int ft_cmd_redirection(t_cmd *cmd, t_token **tokken)
{
	if (ft_strlen((*tokken)->value) > 1)
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
	else
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
	*tokken = (*tokken)->next;
	return (VALID);
}

int ft_cmd_maker(t_cmd *cmd, t_token **tokken)
{
	int i;

	i = 0;
	cmd->arg = NULL;
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
int ft_cmd_pipe(t_cmd *cmd)
{
	cmd->type = PIPE;
	return (VALID);
}
t_cmd *end_list(t_cmd *head)
{
	while(head->next)
		head = head->next;
	return (head);
}

