/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:17 by maw               #+#    #+#             */
/*   Updated: 2025/03/27 17:42:31 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void reset_fd(t_shell *shell)
{
	dup2(shell->STDIN, STDIN_FILENO);
	dup2(shell->STDOUT, STDOUT_FILENO);
	dup2(shell->STDERR, STDERR_FILENO);
}

void save_fd(t_shell *shell)
{
	shell->STDIN = dup(STDIN_FILENO);
	shell->STDOUT = dup(STDOUT_FILENO);
	shell->STDERR = dup(STDERR_FILENO);
}

int ft_direction(t_cmd *cmd)
{
	int infd;
	
	if (cmd->infile != NULL)
	{
		infd = open (cmd->infile, O_RDONLY);
		if (infd == -1)
			return(error(cmd->infile));
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (outfile_direction(cmd) == 0)
		return(error(cmd->infile));
	return (1);
}

int outfile_direction(t_cmd *cmd)
{
	int outfd;

	if (cmd->append == 1)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			return(0);
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	else if (cmd->outfile != NULL)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			return(0);
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	return (1);
}

int here_doc(t_cmd *cmd, t_shell *shell)
{
	int pipefd[2];
	pid_t pid;

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
			return 130;
		}
		dup2(pipefd[0], STDIN_FILENO);
		close (pipefd[0]);
	}
	return (1);
}

void here_doc_child_process(int *pipefd, t_cmd *cmd)
{
	char *del;
	char *line;
	
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
