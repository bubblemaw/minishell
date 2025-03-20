/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:17 by maw               #+#    #+#             */
/*   Updated: 2025/03/20 17:30:23 by masase           ###   ########.fr       */
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
	int outfd;
	
	if (cmd->infile != NULL)
	{
		infd = open (cmd->infile, O_RDONLY);
		if (infd == -1)
			return(error(cmd->infile));
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (cmd->append == 1)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			return(error(cmd->outfile));
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	else if (cmd->outfile != NULL)
	{
		outfd = open (cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			return(error(cmd->outfile));
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	return (1);
}

int here_doc(t_cmd *cmd, t_shell *shell)
{
	char *del;
	char *line;
	int pipefd[2];

	del = ft_strjoin(cmd->delimiter, "\n");
	if (pipe(pipefd) == -1)
		return (error("error occurs during the pipe"));
	while (1)
	{
		write(shell->STDOUT, ">", 1);
		line = get_next_line(shell->STDIN);
		if (!line)
			break ;
		if (ft_strncmp(line, del, ft_strlen(del)) == 0)
		{
			free(line);
			break ;
		}	
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(del);
	dup2(pipefd[0], STDIN_FILENO);
	close (pipefd[0]);
	close (pipefd[1]);
	return (1);
}
