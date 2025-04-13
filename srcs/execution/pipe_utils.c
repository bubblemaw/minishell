/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maw <maw@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:39:52 by maw               #+#    #+#             */
/*   Updated: 2025/04/13 21:42:37 by maw              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipe_exit(int *pipefd, t_shell *shell)
{
	close (pipefd[1]);
	close(pipefd[0]);
	if (shell->prev_pipefd != -1)
		close (shell->prev_pipefd);
	exit(EXIT_FAILURE);
}

void	close_pipe(int *pipefd)
{
	close (pipefd[1]);
	close(pipefd[0]);
}
