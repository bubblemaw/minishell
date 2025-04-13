/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:21:27 by maw               #+#    #+#             */
/*   Updated: 2025/04/13 12:46:12 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	here_doc(t_cmd *cmd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (error("error occurs during the pipe"));
	pid = fork();
	if (pid == 0)
		here_doc_child_process(pipefd, cmd);
	else
	{
		close (pipefd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &shell->exit_status, 0);
		signal(SIGINT, signalhandler);
		if (WEXITSTATUS(shell->exit_status) == 130)
		{
			close (pipefd[0]);
			return (130);
		}
		dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[0]);
	}
	return (1);
}

void	here_doc_child_process(int *pipefd, t_cmd *cmd)
{
	char	*del;
	char	*line;

	signal(SIGINT, signalhandler_heredoc);
	del = ft_strdup(cmd->delimiter);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (ft_strncmp(line, del, ft_strlen(del)) == 0)
		{
			free(line);
			break ;
		}
		line = ft_strjoin(line, "\n");
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(del);
	close (pipefd[0]);
	close (pipefd[1]);
	exit(0);
}
