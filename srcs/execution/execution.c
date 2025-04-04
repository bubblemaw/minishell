/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/04/04 17:09:55 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute(t_shell *shell)
{
	t_cmd *current;
	int	last_status;
	int	pipe_exit_flag;
	
	current = shell->cmd;
	while (current)
	{
		if (current->type == PIPE) // si il ya des operations avec des pipes
		{
			pipex_loop(current, shell);
				break ;
		}
		if (current->infile || current->outfile) // redirection infile outfile
			if (ft_direction(current) == 0)
				return (ERROR);
		if (current->delimiter)
			here_doc(current ,shell);
		else // execution commande basiquee 
			ft_exe(current, shell);
		current = current->next;
	}
	while (wait(&g_exit_status) > 0) // attente de tous les childs process
		last_status = wait_exit_status(shell, &pipe_exit_flag);
	if (pipe_exit_flag == 1)
		g_exit_status = last_status;
	reset_fd(shell);
	return (VALID);
}
int wait_exit_status(t_shell *shell, int *pipe_exit_flag)
{
	int	last_status;

	last_status = 0;
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
	if (shell->cmd->type == PIPE && *pipe_exit_flag != 1)
	{
		last_status = g_exit_status;
		*pipe_exit_flag = 1;
	}
	return (last_status);
}

int	ft_exe(t_cmd *cmd, t_shell *shell) // execution des commandes normales (sans pipe)
{
	pid_t	pid1;
	char	*cmd_path;

	if (cmd->arg == NULL)
		return(ERROR);
	if (built_in(cmd, shell) == VALID)
		return (VALID);
	pid1 = fork();
	if (pid1 == 0)
	{
		cmd_path = ft_parse(cmd, shell);
		if (cmd_path == NULL)
			return(error_cmd(cmd->arg[0]));
		if(execve(cmd_path, cmd->arg, shell->env) == -1)
		{
			if (errno == 13)
				g_exit_status = 126;
			else if (errno == 2)
				g_exit_status = 127;
			return(error_exit("execve failed"));
		}
	}
	else
	{
		waitpid(pid1, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
	}
	return (VALID);
}
