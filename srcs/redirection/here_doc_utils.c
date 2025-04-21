/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:39:51 by masase            #+#    #+#             */
/*   Updated: 2025/04/21 14:41:39 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_line(t_shell *shell, char *line, char *tmp, int *pipefd)
{
	if (shell->here_doc_expan == VALID)
	{
		line = find_var_here_doc(shell, tmp, shell->var);
		if (line == NULL)
			join_free_line(tmp, pipefd);
		else
			join_free_line_expan(line, pipefd);
		if (line)
			free (line);
	}
	else
		join_free_line(tmp, pipefd);
}

void	join_free_line(char *tmp, int *pipefd)
{
	char	*line;

	line = ft_strjoin(tmp, "\n");
	ft_putstr_fd(line, pipefd[1]);
	free(tmp);
	free(line);
}

void	join_free_line_expan(char *tmp, int *pipefd)
{
	char	*line;

	line = ft_strjoin(tmp, "\n");
	ft_putstr_fd(line, pipefd[1]);
	free(line);
}
