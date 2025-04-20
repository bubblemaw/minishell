/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:24:52 by maw               #+#    #+#             */
/*   Updated: 2025/04/20 11:46:13 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(t_shell *shell)
{
	char	*buffer;

	if (shell->prev_pipefd != -1)
		close (shell->prev_pipefd);
	buffer = getcwd(NULL, 0);
	printf("%s\n", buffer);
	free(buffer);
	g_exit_status = 0;
	return (VALID);
}
