/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:16:38 by maw               #+#    #+#             */
/*   Updated: 2025/04/22 22:42:53 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_execute(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd;
	while (current)
	{
		if (current->type == PIPE)
			if (pipex_loop(current, shell) == VALID)
				break ;
		if (exec_redirection(shell, &current) == ERROR)
			return (ERROR);
		if (current == NULL)
			break ;
		if (current->arg && shell->invalid_redir == 0)
			ft_exe(current, shell);
		current = current->next;
		shell->invalid_redir = 0;
	}
	while (wait(&g_exit_status) > 0)
		wait_exit_status();
	reset_fd(shell);
	return (VALID);
}

int	exec_redirection(t_shell *shell, t_cmd **current)
{
	if ((*current)->delimiter)
		if (here_doc(current, shell) == 130)
			return (ERROR);
	if (((*current)->infile) || (*current)->outfile)
		if (ft_direction(current) == 0)
			if (error_redirection(current, shell) == ERROR)
				return (ERROR);
	return (VALID);
}

void	wait_exit_status(void)
{
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = 128 + WTERMSIG(g_exit_status);
}

int	error_redirection(t_cmd **cmd, t_shell *shell)
{
	shell->invalid_redir = 1;
	reset_fd(shell);
	if ((*cmd)->next == NULL)
		return (ERROR);
	else
	{
		while (*cmd && (*cmd)->type != PIPE)
			*cmd = (*cmd)->next;
		if (*cmd)
			return (VALID);
	}
	return (ERROR);
}

int	ft_exe(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid1;
	char	*cmd_path;

	if (cmd->arg == NULL)
		return (ERROR);
	if (built_in(cmd, shell) == VALID)
		return (VALID);
	pid1 = fork();
	if (pid1 == 0)
	{
		cmd_path = ft_parse(cmd, shell);
		if (cmd_path == NULL)
			return (error_cmd(cmd->arg[0]));
		if (execve(cmd_path, cmd->arg, shell->env) == -1)
		{
			put_exit_status();
			return (error_exit(cmd->arg[0]));
		}
	}
	else
	{
		waitpid(pid1, &g_exit_status, 0);
		wait_exit_status();
	}
	return (VALID);
}
