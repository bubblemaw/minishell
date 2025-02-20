/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:17 by maw               #+#    #+#             */
/*   Updated: 2025/02/20 14:18:21 by maw              ###   ########.fr       */
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