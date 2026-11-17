/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:21:27 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 10:00:49 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	here_doc(t_cmd **cmd, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (error("error occurs during the pipe"));
	pid = fork();
	if (pid == 0)
		here_doc_child_process(shell, pipefd, cmd);
	else
	{
		close (pipefd[1]);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &shell->exit_status, 0);
		signal(SIGINT, signalhandler_exec);
		if (WEXITSTATUS(shell->exit_status) == 130)
		{
			close (pipefd[0]);
			shell->exit_status = 130;
			return (130);
		}
		dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[0]);
	}
	return (1);
}

void	here_doc_child_process(t_shell *shell, int *pipefd, t_cmd **cmd)
{
	char	*del;
	char	*tmp;
	char	*line;

	line = NULL;
	signal(SIGINT, signalhandler_heredoc);
	del = ft_strdup((*cmd)->delimiter);
	while (1)
	{
		tmp = readline(">");
		if (!tmp)
			break ;
		if (ft_strncmp(tmp, del, ft_strlen(del)) == 0
			&& ft_strlen(tmp) == ft_strlen(del))
		{
			free(tmp);
			break ;
		}
		manage_line(shell, line, tmp, pipefd);
	}
	free(del);
	close_pipe(pipefd);
	exit(0);
}

void	check_here_doc_expansion(t_token *token, t_shell *shell)
{
	t_token	*tokken;

	tokken = token;
	while (tokken)
	{
		if (tokken->type == REDIRECTION && tokken->value[0] == '<'
			&& tokken->value[1] == '<')
		{
			tokken = tokken->next;
			if (tokken->value[0] == '"' || tokken->value[0] == '\'')
				shell->here_doc_expan = ERROR;
		}
		tokken = tokken->next;
	}
}
