/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:00:01 by maw               #+#    #+#             */
/*   Updated: 2025/03/06 17:29:57 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int create_cmd_lst(t_shell *shell)
{
	t_cmd *current;

	add_cmd_lst(&shell->cmd);
	if (!shell->cmd)
		return (0);
	current = shell->cmd;
	while (shell->tokken)
	{
		if (shell->tokken->type == REDIRECTION)
			ft_cmd_redirection(shell, current);
		else if (shell->tokken->type == COMMAND)
			ft_cmd_maker(shell, current);
		else if (shell->tokken->type == PIPE)
		{
			ft_cmd_pipe(current);
			shell->tokken = shell->tokken->next;
			add_cmd_lst(&shell->cmd);
			current = end_list(shell->cmd);
		}
	}
	return (1);
}

int ft_cmd_redirection(t_shell *shell, t_cmd *cmd)
{
	if (ft_strlen(shell->tokken->value) > 1)
	{
		if (shell->tokken->value[0] == '>' && shell->tokken->value[1] == '>')
		{
		shell->tokken = shell->tokken->next;
		cmd->outfile = ft_strdup(shell->tokken->value);
		cmd->append = 1;
		}	
		if (shell->tokken->value[0] == '<' && shell->tokken->value[1] == '<')
		{
		shell->tokken = shell->tokken->next;
		cmd->delimiter = ft_strdup(shell->tokken->value);
		cmd->type = DELIMITER;
		}
	}
	else
	{
		if (shell->tokken->value[0] == '>')
		{
			shell->tokken = shell->tokken->next;
			cmd->outfile = ft_strdup(shell->tokken->value);
		}	
		else if (shell->tokken->value[0] == '<')
		{
			shell->tokken = shell->tokken->next;
			cmd->infile = ft_strdup(shell->tokken->value);
		}	
	}
	shell->tokken = shell->tokken->next;
	return (1);
}

int ft_cmd_maker(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->arg = NULL;
	while (shell->tokken && (shell->tokken->type == OPTION || shell->tokken->type == ARGUMENT || shell->tokken->type == COMMAND))
	{
		printf("je suis dans le cmd maker \n");
		printf("le token en question : %s \n", shell->tokken->value);
		cmd->arg = ft_realloc(cmd->arg, i * sizeof(char *), (i + 1) * sizeof(char *));
		cmd->arg[i] = ft_strdup(shell->tokken->value);
		if (cmd->arg == NULL)
			return (0);
		i++;
		shell->tokken = shell->tokken->next;
	}
	cmd->arg[i] = NULL;
	return (1);
}
int ft_cmd_pipe(t_cmd *cmd)
{
	cmd->type = PIPE;
	return (0);
}
t_cmd *end_list(t_cmd *head)
{
	while(head->next)
		head = head->next;
	return (head);
}
