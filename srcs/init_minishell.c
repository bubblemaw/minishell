/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masase <masase@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:31:21 by maw               #+#    #+#             */
/*   Updated: 2025/02/27 18:34:31 by masase           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void init_execution(t_shell *shell, char **env)
{
	shell->prev_pipefd = -1;
	save_fd(shell);
	shell->env = env;
}