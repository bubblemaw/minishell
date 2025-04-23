/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:17 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:32:42 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_fd(t_shell *shell)
{
	dup2(shell->stdin_, STDIN_FILENO);
	dup2(shell->stdout_, STDOUT_FILENO);
	dup2(shell->stderr_, STDERR_FILENO);
}

void	save_fd(t_shell *shell)
{
	shell->stdin_ = dup(STDIN_FILENO);
	shell->stdout_ = dup(STDOUT_FILENO);
	shell->stderr_ = dup(STDERR_FILENO);
}

int	ft_direction(t_cmd **cmd, t_shell *shell)
{
	int	infd;

	if ((*cmd)->infile != NULL)
	{
		infd = open ((*cmd)->infile, O_RDONLY);
		if (infd == -1)
		{
			shell->exit_status = 1;
			perror((*cmd)->infile);
			return (0);
		}
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (outfile_direction(cmd) == 0)
	{
		shell->exit_status = 1;
		perror((*cmd)->outfile);
		return (0);
	}
	return (1);
}

int	outfile_direction(t_cmd **cmd)
{
	int	outfd;

	if ((*cmd)->append == 1)
	{
		outfd = open ((*cmd)->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			return (0);
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	else if ((*cmd)->outfile != NULL)
	{
		outfd = open ((*cmd)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			return (0);
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	return (1);
}
