/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:20:25 by masase            #+#    #+#             */
/*   Updated: 2025/04/23 09:37:37 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex_loop(t_cmd *current, t_shell *shell)
{
	ft_test_direction(current);
	while (current)
	{
		while (current && current->valid == ERROR)
			current = current->next;
		if (!current)
			break ;
		if (piper(current, shell) == CHILD_PROCESS)
		{
			if (current->arg)
				ft_exe_pipe(current, shell);
			else
				exit (0);
		}
		else
			current = current->next;
	}
	return (VALID);
}

int	child_processor(t_cmd *cmd, t_shell *shell, int *pipefd)
{
	if (shell->prev_pipefd != -1)
	{
		dup2(shell->prev_pipefd, STDIN_FILENO);
		close(shell->prev_pipefd);
	}
	if (cmd->infile)
		if (ft_direction(&cmd, shell) == 0)
			close_pipe_exit(pipefd, shell);
	if (cmd->outfile)
	{
		if (ft_direction(&cmd, shell) == 0)
			close_pipe_exit(pipefd, shell);
	}
	else if (cmd->next == NULL)
	{
		close_pipe(pipefd);
		dup2(shell->stdout_, STDOUT_FILENO);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
	}
	return (CHILD_PROCESS);
}

int	piper(t_cmd *cmd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (error("error occurs during the pipe"));
	pid = fork();
	if (pid == -1)
		return (error("error occurs during the fork"));
	if (pid == 0)
		return (child_processor(cmd, shell, pipefd));
	else
	{
		if (shell->prev_pipefd != -1)
			close(shell->prev_pipefd);
		close(pipefd[1]);
		shell->prev_pipefd = pipefd[0];
		return (PARENT_PROCESS);
	}
}

int	ft_exe_pipe(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	if (built_in_pipe(cmd, shell) == VALID)
	{
		return (VALID);
	}
	cmd_path = ft_parse(cmd, shell);
	if (cmd_path == NULL)
		return (error_cmd(cmd->arg[0]));
	if (execve(cmd_path, cmd->arg, shell->env) == -1)
		return (error_exit("execve failed", shell));
	return (VALID);
}
