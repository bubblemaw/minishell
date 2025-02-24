/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:17 by maw               #+#    #+#             */
/*   Updated: 2025/02/24 18:41:41 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
int ft_direction(t_token *token)
{
	int infd;
	int outfd;
	
	if (token->infile)
	{
		infd = open (token->infile, O_RDONLY);
		if (infd == -1)
			return(error("erreur open du fichier"));
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (token->outfile)
	{
		outfd = open (token->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			return(error("erreur open du fichier"));
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	return (1);
}

int here_doc(t_token *token, t_shell *shell)
{
	char *del;
	char *line;
	int here_fd;

	del = token->delimiter;
	here_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (here_fd == -1)
		return(error("erreur open du fichier"));
	while (1)
	{
		ft_printf("je lis \n");
		line = get_next_line(shell->STDIN);
		if (ft_strncmp(line, del, ft_strlen(del)) == 0)
		{
			free(line);
			break ;
		}	
		ft_putstr_fd(line, here_fd);
		free(line);
	}

	dup2(here_fd, STDIN_FILENO);
	return (1);
}