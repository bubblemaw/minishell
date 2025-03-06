/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchellen <dchellen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:31:21 by maw               #+#    #+#             */
/*   Updated: 2025/03/06 15:35:47 by dchellen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_execution(t_shell *shell, char **env)
{
	shell->prev_pipefd = -1;
	save_fd(shell);
	shell->env = env;
	shell->cmd = NULL;
	shell->tokken = NULL;
}