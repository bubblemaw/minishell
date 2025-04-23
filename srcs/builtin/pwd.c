/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:24:52 by maw               #+#    #+#             */
/*   Updated: 2025/04/23 09:28:43 by dchellen         ###   ########.fr       */
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
	shell->exit_status = 0;
	return (VALID);
}
